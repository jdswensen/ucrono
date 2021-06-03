#!/usr/bin/env pwsh
. $PSScriptRoot/env.ps1

if ( -Not (Test-Path -Path ${NRF_SDK_INSTALL_PATH})) {
    Write-Host "Nordic SDK does not exist in expected path."
    Invoke-Expression -Command "$PSScriptRoot/dl-nrf-sdk.ps1"
}

New-Item -ItemType "directory" -Path ${BUILD_DIR} -Force | Out-Null
Copy-Item -Path ${NRF_SDK_INSTALL_PATH} -Destination ${BUILD_DIR}/ -Recurse -Force