<script lang="ts">
  import Wrapper from "./wrapper.svelte";
  import { performConnect, performDisconnect, connectionMessage, isConnected, isConnecting, isError } from "./lib/connection.svelte";

  const connectStatusColor = $derived(isError() ? "text-danger" : "text-dark");

  let driveSpeedValue = $state(0);
  let driveDirectionValue = $state(0);
</script>

<Wrapper 
  connectButtonAction={!isConnected() ? performConnect : performDisconnect} 
  connectButtonDisabled={!isConnected() ? isConnecting() : false} 
  connectButtonText={!isConnected() ? "Activate" : "Deactivate"} 
  statusColor={!isConnected() ? "text-danger" : "text-success"} 
  statusText={!isConnected() ? "Inactive" : "Active"} 
  favicon={!isConnected() ? "/walleBox.ico" : "/walleActive.ico"}>

  {#if !isConnected()}

  <h1 class="fs-4 card-title fw-bold mb-4 text-center">WALL-E Controller</h1>
  <p class="card-subtitle text-center">Remote Control using WebSockets</p>

  {:else}

  <label for="customRange3" class="form-label">Driving Speed: {driveSpeedValue}</label>
  <input type="range" class="form-range" min="-100" max="100" bind:value={driveSpeedValue}>
  <label for="customRange3" class="form-label">Driving Direction: {driveDirectionValue}</label>
  <input type="range" class="form-range" min="-100" max="100" bind:value={driveDirectionValue}>

  {/if}

</Wrapper>