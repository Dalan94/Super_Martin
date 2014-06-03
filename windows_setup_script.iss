; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{B151DD23-0E4A-4583-A392-C5D1DC71E8CA}
AppName=Super Martin
AppVersion=1.0
;AppVerName=Super Martin 1.0
AppPublisher=INSA de Rennes
AppPublisherURL=https://github.com/Dalan94/Super_Martin
AppSupportURL=https://github.com/Dalan94/Super_Martin
AppUpdatesURL=https://github.com/Dalan94/Super_Martin
DefaultDirName={pf}\Super Martin
DefaultGroupName=Super Martin
AllowNoIcons=yes
LicenseFile=E:\Travail\Langage_C\Semestre_2\Super_Martin\LICENSE
OutputDir=E:\Travail\Langage_C\Semestre_2\Super_Martin
OutputBaseFilename=Super_Martin_setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "Release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Release\Super_Martin\save\.save"; DestDir: "{app}\Super_Martin\save";
Source: "Release\Level_Editor\.conf"; DestDir: "{app}\Level_Editor";
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Super Martin"; Filename: "{app}\super_martin.bat"
Name: "{group}\Super Martin Level Editor"; Filename: "{app}\level_editor.bat"
Name: "{group}\{cm:UninstallProgram,Super Martin}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Super Martin"; Filename: "{app}\super_martin.bat"; Tasks: desktopicon
Name: "{commondesktop}\Super Martin Level Editor"; Filename: "{app}\level_editor.bat"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Super Martin"; Filename: "{app}\super_martin.bat"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\super_martin.bat"; Description: "{cm:LaunchProgram,Super Martin}"; Flags: shellexec postinstall skipifsilent

