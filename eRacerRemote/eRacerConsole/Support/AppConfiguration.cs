namespace eRacerRemote.Support;

public class AppConfiguration
{
    public string BrokerUrl { get; set; }
    public int BrokerPort { get; set; }
    public string ClientId { get; set; }
    public string UserName { get; set; }
    public string Password { get; set; }
    public string TopicCommand { get; set; }
    public string TopicResponse { get; set; }
}