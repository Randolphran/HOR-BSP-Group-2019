program DIPatternMatchInterrupt;

{$R 'DIPatternMatchInterruptResource.res' 'DIPatternMatchInterruptResource.rc'}

uses
  Forms,
  Main in 'Main.pas' {MainForm},
  GifImage in '..\GifImage.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
