#!/usr/bin/env pwsh
. $PSScriptRoot/env.ps1

Copy-Item $PSScriptRoot/../main.c -Destination $NRF_SDK_LOCAL/$NRF_TIMER_EXAMPLE_PATH/$MAIN  
Copy-Item $PSScriptRoot/../timer_pca10040.emProject -Destination $NRF_SDK_LOCAL/$NRF_TIMER_EXAMPLE_PATH/$PROJ
