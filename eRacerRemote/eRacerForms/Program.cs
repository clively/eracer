//using Microsoft.Extensions.DependencyInjection;

using eRacerCommon.Interfaces;
using eRacerCommon.Services;
using eRacerCommon.Support;
using eRacerForms.Support;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace eRacerForms
{
	internal static class Program
	{
		/// <summary>
		///  The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			// To customize application configuration such as set high DPI settings or default font,
			// see https://aka.ms/applicationconfiguration.

			Application.SetHighDpiMode(HighDpiMode.SystemAware);
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);

			var host = CreateApplicationBuilder();
			
			Application.Run(host.Services.GetRequiredService<MainForm>());
		}

		public static IServiceProvider? ServiceProvider { get; private set; }

		private static IHost CreateApplicationBuilder()
		{
			//Host.CreateApplicationBuilder

			HostApplicationBuilderSettings settings = new()
			{
				Args = new string[0],
				Configuration = new ConfigurationManager(),
				ContentRootPath = Directory.GetCurrentDirectory(),
			};

			settings.Configuration.AddJsonFile("Configuration\\Config.json", optional: false);

			var builder = Host.CreateApplicationBuilder(settings);

			builder.Logging.ClearProviders();
			builder.Logging.AddInternalLogger(config =>
												config.MaximumEntries = 100);

			builder.Services.Configure<AppConfiguration>(builder.Configuration.GetSection("MqSetup"));

			builder.Services.AddSingleton<IMqHandler, MqHandler>(); // add the MqHandler to the service collection.
			builder.Services.AddTransient<MainForm>();


			return builder.Build();
			
		}
	}
}