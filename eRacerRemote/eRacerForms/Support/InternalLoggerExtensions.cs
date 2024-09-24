using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Configuration;

namespace eRacerForms.Support;

public static class InternalLoggerExtensions
{
	public static ILoggingBuilder AddInternalLogger(this ILoggingBuilder builder)
	{
		builder.AddConfiguration();

		builder.Services.TryAddEnumerable(
			ServiceDescriptor.Singleton<ILoggerProvider, InternalLoggerProvider>());

		LoggerProviderOptions.RegisterProviderOptions
			<InternalLoggerConfiguration, InternalLoggerProvider>(builder.Services);

		return builder;
	}

	public static ILoggingBuilder AddInternalLogger(
		this ILoggingBuilder builder,
		Action<InternalLoggerConfiguration> configure)
	{
		builder.AddInternalLogger();
		builder.Services.Configure(configure);

		return builder;
	}
}
