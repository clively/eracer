namespace eRacerRemote.Support;

public static class ExtraCommands
{
    public static void EmitHelp()
    {
        Console.WriteLine(
@"-----------------------------
	Racer Remote
			
	FWD:[SPEED]:[TIME]	- Move Forward 
	RVS:[SPEED]:[TIME]	- Move Backward

	LFT:[SPEED]:[TIME]	- Turn Left
	RGT:[SPEED]:[TIME]	- Turn Right

	SET:[NAME]			- Set the name of the racer to control	
	EXIT = Quite Program		
			
	[SPEED] ranges from 1 to 255.  Where 1 is slowest and 255 is fastest.
	[TIME] is a value in seconds from 1 to 60
");


    } // method::EmitHelp

    public static void EmitNotSupported(string cmd)
    {
        Console.WriteLine($"Command [{cmd}] is not currently supported.");
    } // method::NotSupported
}
