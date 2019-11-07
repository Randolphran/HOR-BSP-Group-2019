program DIInterrupt;

{$R 'DIInterruptResource.res' 'DIInterruptResource.rc'}

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
