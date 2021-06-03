#!/usr/bin/env pwsh
. $PSScriptRoot/env.ps1

Copy-Item $NRF_SDK_LOCAL/$NRF_TIMER_EXAMPLE_PATH/$MAIN -Destination $PSScriptRoot/..
Copy-Item $NRF_SDK_LOCAL/$NRF_TIMER_EXAMPLE_PATH/$PROJ -Destination $PSScriptRoot/..