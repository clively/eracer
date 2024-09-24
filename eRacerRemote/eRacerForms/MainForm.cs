using eRacerCommon.Interfaces;
using eRacerCommon.Services;
using eRacerCommon.Support;
using eRacerForms.Support;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using Microsoft.VisualBasic.Logging;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Threading;
using System.Windows.Forms;
using eRacerForms.Interfaces;

namespace eRacerForms;

public partial class MainForm : Form
{
	bool isConnected = false;

	private readonly IMqHandler _mqHandler;
	private readonly ILogger _logger;


	public MainForm(IMqHandler mqHandler,
					ILogger<MqHandler> logger)
	{
		InitializeComponent();
		_mqHandler = mqHandler;
		_logger = logger;


	} // constructor

	private void BtnSetName_Click(object sender, EventArgs e)
	{
		if (!isConnected) return;

		if (!String.IsNullOrEmpty(TxtRacerName.Text))
		{
			_mqHandler.MqttTopicCommand = TxtRacerName.Text;
			_logger.LogInformation("Name set to: {RacerName}", TxtRacerName.Text); 
		}
	}

	private async void BtnConnect_Click(object sender, EventArgs e)
	{
		tmrUpdateLog.Enabled = true;
		await _mqHandler.InitializeAsync();
		isConnected = true;
	}

	private void TmrUpdateLog_Tick(object sender, EventArgs e)
	{
		/// ask the logger for the current data
		/// // do I typecast it back to a InternalLogger ?  that don't work either.
		var log = _logger as InternalLogger;

	https://stackoverflow.com/questions/65443870/can-a-serilog-ilogger-be-converted-to-a-microsoft-extensions-logging-ilogger


		_logger.

		// this won't work because the logger is passed to this as a different interface entirely.
		// so how the hell do I get the right thing??
		LoggingBox.Rtf = log?.GetLogAsRichText(true) ?? string.Empty;
		LoggingBox.ScrollToBottom();
	}
}
