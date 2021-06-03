#!/usr/bin/env pwsh
. $PSScriptRoot/env.ps1

if (Test-Path -Path $NRF_SDK_INSTALL_PATH) {
    Write-Host "File already exists at that location."
} else {
    Write-Host "Downloading"

    $DL="${NRF5_DL_DIR}/${NRF5_SDK_NAME}.zip"
    Invoke-WebRequest -Uri ${NRF5_SDK_URL} -Method Get -OutFile ${DL}
    Expand-Archive -Path ${DL} -DestinationPath ${NRF_SDK_INSTALL_DIR}
    Remove-Item ${DL}
}
