using MQTTnet;
using MQTTnet.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Authentication;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace eRacerRemote;

public class MqHandler
{
	private IMqttClient mqttClient;

	public String MqttBrokerUrl { get; set; }
	public String MqttTopicCommand { get; set; }
	public String MqttTopicResponse {get; set; }
	public int MqttPort { get; set; }
	public String MqttClientId { get; set; }
	public String MqttUsername { get; set; }
	public String MqttPassword { get; set; }

	public Boolean KeepAlive { get; set; } = false;

	public MqHandler()
	{
	} // constructor

	private Task OnApplicationMessageReceivedAsync(MqttApplicationMessageReceivedEventArgs eventArgs)
	{
		String msg = Encoding.UTF8.GetString(eventArgs.ApplicationMessage.PayloadSegment);
		Console.WriteLine($"---Message from {MqttClientId}");
		Console.WriteLine($"{msg}");
		Console.WriteLine("---");

		return Task.CompletedTask;
	} // method::OnApplicationMessageReceivedAsync


	public async Task InitializeAsync()
	{
		KeepAlive = true;
		// Create a MQTT client factory
		var factory = new MqttFactory();

		// Create a MQTT client instance
		mqttClient = factory.CreateMqttClient();

		X509Certificate2[] certificate = { new(File.ReadAllBytes("D:\\GitProjects\\eracer\\eRacerRemote\\Config\\emqxsl-ca.crt")) };

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
			Console.WriteLine("Connected to MQTT broker successfully.");

			// Subscribe to a topic
			// we might use this to have the car send data back.
			await mqttClient.SubscribeAsync(MqttTopicResponse);

			// Callback function when a message is received
			mqttClient.ApplicationMessageReceivedAsync += OnApplicationMessageReceivedAsync;

			Console.WriteLine("Connected to MQTT broker");

		} else
		{
			Console.WriteLine($"Failed to connect to MQTT broker: {connectResult.ResultCode}");
		}
	} // method::Connect

	public void SendMessage(string message)
	{
		mqttClient.PublishStringAsync(MqttTopicCommand, message);
	} // method::SendMessage

} // class::MqHandler
