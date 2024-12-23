<script lang="ts">
  import { fade, slide } from 'svelte/transition';
  import SliderControl from "./SliderControl.svelte";
  import SwitchControl from "./SwitchControl.svelte";
  import DriveControl from "./DriveControl.svelte";
  import { activateConnection, deactivateConnection, isConnected, lastMessage } from "./lib/connection.svelte";
</script>

<svelte:head>
  <link rel="icon" type="image/svg" href="{!isConnected() ? "./walleBox.ico" : "./walleActive.ico"}?a=1"/>
  <title>WALL-E {!isConnected() ? "Inactive" : "Active"} - RoCCI e.V.</title>
</svelte:head>

<section class="h-100">
  <div class="container h-100">
      <div class="row justify-content-sm-center h-100">
          <div class="col-xxl-4 col-xl-5 col-lg-5 col-md-7 col-sm-9">
            {#if !isConnected()}
            <div class="text-center" transition:slide>
                <img class="py-5" src="./walle.png" alt="" width="100"><br>
            </div>
            {/if}
            <div class="card shadow-lg">
                <div class="card-header py-3 border-0">
                    <div class="row">
                        <div class="col-sm-4 text-sm-start text-center mb-sm-0 mb-3">
                            <button onclick={!isConnected() ? activateConnection : deactivateConnection} class="btn btn-primary ms-auto">{!isConnected() ? "Activate" : "Deactivate"}</button>
                        </div>
                        <div class="col-sm m-auto text-center">
                            Status: <strong class="{!isConnected() ? "text-danger" : "text-success"} ">{!isConnected() ? "Inactive" : "Active"} </strong>
                        </div>
                    </div>
                </div>
                <div class="card-body px-5 pb-5 pt-2">

                  {#if !isConnected()}
                    <h1 class="fs-4 card-title fw-bold mb-4 mt-4 text-center">WALL-E Controller</h1>
                    <p class="card-subtitle text-center" >Remote Control using WebSockets</p>
                  {:else}
                    <DriveControl></DriveControl>
                    <SliderControl code={"SHEADT"} name={"Example Servo"} value={0} min={0} max={180}></SliderControl>
                    <SwitchControl code={"ELIGHT"} name={"Green Light"} value={false}></SwitchControl>
                  {/if}

                </div>

                {#if isConnected()}
                  <div class="card-footer py-3 border-0 text-center">
                    <em>{lastMessage()}</em>
                  </div>
                {/if}

            </div>
            {#if !isConnected()}
            <div class="text-center mt-5 text-muted" transition:fade>
                Copyright &copy; 2025 <a href="https://rocci.net/impressum" target="_blank" class="text-reset">RoCCI e.V.</a> - All rights reserved
            </div>
            {/if}
          </div>
      </div>
  </div>
</section>
<div id="joyDiv" style="height: 200px; width: 200px;"></div>