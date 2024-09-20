// See https://aka.ms/new-console-template for more information
using eRacerRemote.Services;
using eRacerRemote.Support;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.DependencyInjection;
using eRacerRemote.Interfaces;
using Microsoft.Extensions.Logging;

HostApplicationBuilderSettings settings = new()
{
	Args = args,
	Configuration = new ConfigurationManager(),
	ContentRootPath = Directory.GetCurrentDirectory(),
};

settings.Configuration.AddJsonFile("Configuration\\Config.json", optional: false);
settings.Configuration.AddCommandLine(args);

var builder = Host.CreateApplicationBuilder(settings);

builder.Services.Configure<AppConfiguration>(builder.Configuration.GetSection("MqSetup"));

builder.Services.AddSingleton<IMqHandler, MqHandler>(); // add the MqHandler to the service collection.

/* logging */
using ILoggerFactory factory = LoggerFactory.Create(builder => builder.AddConsole());
ILogger logger = factory.CreateLogger("Program");


logger.LogInformation("It begins");

/* setup host */
using IHost host = builder.Build();

/* and away we go */
var mqHandler = host.Services.GetRequiredService<IMqHandler>();

/*
 * We could host our own MQ server....
 * https://test.mosquitto.org/
 */

await mqHandler.InitializeAsync();
Boolean continueRunning = true;
String lastCommand = String.Empty;

while (continueRunning)
{
	Console.WriteLine("By Your Command:");

	String cmd = Console.ReadLine()!.Trim().ToUpper();
	Boolean cmdHandled = false;

	// switch doesn't work with StartsWith
	if (cmd.StartsWith("EXIT"))
	{
		continueRunning = false;
		cmdHandled = true;
	}

	if (cmd.StartsWith("SET:"))
	{
		String newRacerName = cmd.Trim().ToUpper().Remove(0, 4);
		if (!string.IsNullOrEmpty(newRacerName))
		{
			mqHandler.MqttTopicCommand = newRacerName;
			Console.WriteLine("Racer Name Updated");
		} else
		{
			Console.WriteLine("You must enter a NAME for the racer.  Exa:  SET:RACER001");
		}
		cmdHandled = true;
	}

	if (cmd.StartsWith("HELP"))
	{
		ExtraCommands.EmitHelp();
		cmdHandled = true;
	}

	if (cmd == "R")
	{
		// replay command
		mqHandler.SendMessage(lastCommand);
		Console.WriteLine("Message Sent");
	}

	if (!cmdHandled)
	{
		mqHandler.SendMessage(cmd);
		lastCommand = cmd;
		Console.WriteLine("Message Sent");
	}

//	await Task.Delay(5000); // Wait for 5 seconds
	Console.WriteLine("");
}

Console.WriteLine("program done.");
