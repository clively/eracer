using eRacerCommon.Interfaces;
using eRacerCommon.Support;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using MQTTnet;
using MQTTnet.Client;
using System.Security.Authentication;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace eRacerCommon.Services;

public class MqHandler : IMqHandler
{
	private IMqttClient? mqttClient;

	public string MqttBrokerUrl { get; set; } = "";
	public string MqttTopicCommand { get; set; } = "";
	public string MqttTopicResponse { get; set; } = "";
	public int MqttPort { get; set; } = 0;
	public string MqttClientId { get; set; } = "";
	public string MqttUsername { get; set; } = "";
	public string MqttPassword { get; set; } = "";

	public bool KeepAlive { get; set; } = false;

	/* avert your eyes from my privates */
	private ILogger _logger;
	private string _certLocation = "";

	public MqHandler(IOptions<AppConfiguration> appConfig,
					ILogger<MqHandler> logger)
	{
		if (appConfig.Value != null)
		{
			MqttBrokerUrl = appConfig.Value.BrokerUrl;
			MqttTopicCommand = appConfig.Value.TopicCommand;
			MqttTopicResponse = appConfig.Value.TopicResponse;
			MqttPort = appConfig.Value.BrokerPort;
			MqttClientId = appConfig.Value.ClientId;
			MqttUsername = appConfig.Value.UserName;
			MqttPassword = appConfig.Value.Password;
			_certLocation = appConfig.Value.CertLocation;
		} // if appConfig.value

		_logger = logger;
	} // constructor

	private Task OnApplicationMessageReceivedAsync(MqttApplicationMessageReceivedEventArgs eventArgs)
	{
		string msg = Encoding.UTF8.GetString(eventArgs.ApplicationMessage.PayloadSegment);

		_logger.LogInformation("[{RacerName}] says {Message}", MqttTopicCommand, msg);

		return Task.CompletedTask;
	} // method::OnApplicationMessageReceivedAsync


	public async Task InitializeAsync()
	{
		KeepAlive = true;
		// Create a MQTT client factory
		var factory = new MqttFactory();

		// Create a MQTT client instance
		mqttClient = factory.CreateMqttClient();

		X509Certificate2[] certificate = { new(File.ReadAllBytes(_certLocation)) };

		// Create MQTT client options
		var options = new MqttClientOptionsBuilder()
			.WithTcpServer(MqttBrokerUrl, MqttPort) // MQTT broker address and port
			.WithCredentials(MqttUsername, MqttPassword) // Set username and password
			.WithClientId(MqttClientId)
			.WithCleanSession()
			.WithTlsOptions(
				o =>
				{
					o.UseTls(true);

					o.WithIgnoreCertificateChainErrors(true); // ignore all cert problems
					o.WithAllowUntrustedCertificates(true); // I don;t care if it's not valid or intercepted or whatever ignore all cert problems

					o.WithSslProtocols(SslProtocols.Tls12);

					// Please provide the file path of your certificate file. The current directory is /bin.
					o.WithClientCertificates(certificate);
				}
			)
			.Build();

		// Connect to MQTT broker
		var connectResult = await mqttClient.ConnectAsync(options);

		if (connectResult.ResultCode == MqttClientConnectResultCode.Success)
		{
			_logger.LogInformation("MQTT broker connected successfully.");

			// Subscribe to a topic
			// we might use this to have the car send data back.
			await mqttClient.SubscribeAsync(MqttTopicResponse);

			// Callback function when a message is received
			mqttClient.ApplicationMessageReceivedAsync += OnApplicationMessageReceivedAsync;


		} else
		{
			_logger.LogInformation("MQTT broker failed [{ResultCode}]", connectResult.ResultCode);
		}
	} // method::Connect

	public void SendMessage(string message)
	{
		if (mqttClient == null) return;

		mqttClient.PublishStringAsync(MqttTopicCommand, message);
	} // method::SendMessage


} // class::MqHandler
