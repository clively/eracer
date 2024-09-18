// See https://aka.ms/new-console-template for more information
using eRacerRemote;

Console.WriteLine("Hello, World!");

var ct = new CancellationTokenSource();

MqHandler mqHandler = new()
{
	MqttBrokerUrl = "yde4f5d3.ala.us-east-1.emqxsl.com",
	MqttClientId = "DASH001",
	MqttPort = 8883,
	MqttTopicCommand = "eRaceCmd",
	MqttTopicResponse = "eRaceRsp",
	MqttUsername = "LCDashboard",
	MqttPassword = "Funny@004a"

};

Console.WriteLine("kicking off the mq handler");

await mqHandler.InitializeAsync();

String cmd = String.Empty;


while (true)
{
	Console.WriteLine("By Your Command:");

	cmd = Console.ReadLine()!;

	if (cmd == "exit")
	{
		break;
	}

	mqHandler.SendMessage(cmd);
	Console.WriteLine("Message Sent");

	await Task.Delay(5000); // Wait for 5 seconds
	Console.Write(".");
}

Console.WriteLine("program done.");
