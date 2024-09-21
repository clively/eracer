namespace eRacerCommon.Interfaces;

public interface IMqHandler
{
	/* properties used by anything implementing this */
	String MqttBrokerUrl { get; set; }
	String MqttTopicCommand { get; set; }
	String MqttTopicResponse { get; set; }
	int MqttPort { get; set; }
	String MqttClientId { get; set; }
	String MqttUsername { get; set; }
	String MqttPassword { get; set; }

	Boolean KeepAlive { get; set; }


	/* methods */
	Task InitializeAsync();
	void SendMessage(string message);
}

