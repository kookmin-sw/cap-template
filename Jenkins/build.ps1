param(
    [string]$Version="version.value.error",
    [string]$RefreshToken="refresh.token.error",
    [string]$ClientID="client.id.error",
    [string]$ClientSecret="client.secret.error",
    [string]$FolderID="folder.id.error"
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

# Set the Google Auth parameters. Fill in your RefreshToken, ClientID, and ClientSecret
$Params = @{
    Uri = 'https://accounts.google.com/o/oauth2/token'
    Body = @(
        "refresh_token=$RefreshToken", # Replace $RefreshToken with your refresh token
        "client_id=$ClientID",         # Replace $ClientID with your client ID
        "client_secret=$ClientSecret", # Replace $ClientSecret with your client secret
        "grant_type=refresh_token"
    ) -join '&'
    Method = 'Post'
    ContentType = 'application/x-www-form-urlencoded'
}
$AccessToken = (Invoke-RestMethod @Params).access_token

# Change this to the file you want to upload
$SourceFile = $ZipPath

# Get the source file contents and details, encode in base64
$SourceItem = Get-Item $SourceFile
$SourceMime = [System.Web.MimeMapping]::GetMimeMapping($SourceItem.FullName)

try {
    $BlockSize = $Base64Transform.InputBlockSize * 4
    $Buffer = New-Object byte[] $BlockSize
    $BytesRead = $null

    do {
        $BytesRead = $BinaryReader.Read($Buffer, 0, $BlockSize)

        if ($BytesRead -gt 0) {
            $TransformedBytes = $Base64Transform.TransformFinalBlock($Buffer, 0, $BytesRead)
            $Base64String = [Text.Encoding]::UTF8.GetString($TransformedBytes)
            Write-Output $Base64String
        }
    } while ($BytesRead -gt 0)
}
finally {
    $Base64Transform.Dispose()
    $BinaryReader.Dispose()
    $FileStream.Dispose()
}

$SourceBase64 = $Base64String

# If uploading to a Team Drive, set this to 'true'
$SupportsTeamDrives = 'false'

# Set the file metadata
$UploadMetadata = @{
    originalFilename = $sourceItem.Name
    name = $sourceItem.Name
    description = $sourceItem.VersionInfo.FileDescription
    parents = @($FolderID) # Include to upload to a specific folder
    #teamDriveId = ‘teamDriveId’            # Include to upload to a specific teamdrive
}

# Set the upload body
$UploadBody = @"
--boundary
Content-Type: application/json; charset=UTF-8

$($UploadMetadata | ConvertTo-Json)
--boundary
Content-Transfer-Encoding: base64
Content-Type: $SourceMime

$SourceBase64
--boundary--
"@

# Set the upload headers
$UploadHeaders = @{
    "Authorization" = "Bearer $AccessToken"
    "Content-Type" = 'multipart/related; boundary=boundary'
    "Content-Length" = $UploadBody.Length
}

# Perform the upload
$Response = Invoke-RestMethod -Uri "https://www.googleapis.com/upload/drive/v3/files?uploadType=multipart&SupportsTeamDrives=$SupportsTeamDrives" -Method Post -Headers $UploadHeaders -Body $UploadBody

# Print the response
$Response