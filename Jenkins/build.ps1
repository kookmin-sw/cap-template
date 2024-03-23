param(
    [string]$Version="version.value.error"
)

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$BuildPath = "C:\\Work\\Career\\2_KMU\\CapstoneProject\\Builds"
$VersionPath = $BuildPath + "\\" + $Version

# Move to the build directory
Set-Location $BuildPath

# If the build already exists, delete it
if (Test-Path $VersionPath) {
    Remove-Item -Recurse -Force $VersionPath
}

# If the zip file already exists, delete it
$ExistZipPath = $VersionPath + ".zip"
if (Test-Path $ExistZipPath) {
    Remove-Item -Force $ExistZipPath
}

# Create a new folder for the build
New-Item -ItemType Directory -Name $Version

# Run the build
$RunUATPath = "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Build\\BatchFiles\\RunUAT.bat" 
$ProjectOption = "-project=C:\\ProgramData\\Jenkins\\.jenkins\\workspace\\capstone-2024-20\\capstone_2024_20\\capstone_2024_20.uproject" 
$ArchivePath = Resolve-Path($Version)
$ArchiveOption = "-archivedirectory="+$ArchivePath
$UATOptions = @("BuildCookRun", $ProjectOption, "-Distribution", "-stage", "-pak", "-build", "-cook", "-prereqs", "-package", "-archive", $ArchiveOption)
Start-Process -FilePath $RunUATPath -ArgumentList $UATOptions -NoNewWindow -Wait

# Make a zip file of the build
$ZipPath = $ArchivePath.ToString() + ".zip"
Compress-Archive -Path $ArchivePath -DestinationPath $ZipPath -Force
