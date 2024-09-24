using System.Collections.Concurrent;
using System.Runtime.Versioning;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

namespace eRacerForms.Support;

[UnsupportedOSPlatform("browser")]
[ProviderAlias("Internal")]
public sealed class InternalLoggerProvider : ILoggerProvider
{
	private readonly IDisposable? _onChangeToken;
	private InternalLoggerConfiguration _currentConfig;
	private readonly ConcurrentDictionary<string, InternalLogger> _loggers =
		new(StringComparer.OrdinalIgnoreCase);

	public InternalLoggerProvider(
		IOptionsMonitor<InternalLoggerConfiguration> config)
	{
		_currentConfig = config.CurrentValue;
		_onChangeToken = config.OnChange(updatedConfig => _currentConfig = updatedConfig);
	}

	public ILogger CreateLogger(string categoryName) =>
		_loggers.GetOrAdd(categoryName, name => new InternalLogger(name, GetCurrentConfig));

	private InternalLoggerConfiguration GetCurrentConfig() => _currentConfig;

	public void Dispose()
	{
		_loggers.Clear();
		_onChangeToken?.Dispose();
	}
}
