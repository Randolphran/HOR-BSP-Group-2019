program StaticAO;

uses
  Forms,
  Main in 'Main.pas' {MainForm},
  DaqUtils in '..\DaqUtils.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
