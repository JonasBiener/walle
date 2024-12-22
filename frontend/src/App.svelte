<script lang="ts">
  import Wrapper from "./wrapper.svelte";
  import { performConnect, performDisconnect, connectionMessage, isConnected, isConnecting, isError } from "./lib/connection.svelte";

  const connectStatusColor = $derived(isError() ? "text-danger" : "text-dark");

  let driveSpeedValue = $state(0);
  let driveDirectionValue = $state(0);
</script>

{#if !isConnected()}

<Wrapper connectButtonAction={performConnect} connectButtonDisabled={isConnecting()} connectButtonText={"Connect"} statusColor={connectStatusColor} statusText={connectionMessage()}>
  <h1 class="fs-4 card-title fw-bold mb-4 text-center">WALL-E Controller</h1>
  <p class="card-subtitle text-center">Remote Control via the Web Bluetooth API</p>
</Wrapper>

{:else}

<Wrapper connectButtonAction={performDisconnect} connectButtonDisabled={false} connectButtonText={"Disconnect"} statusColor={"text-success"} statusText={"Connected"}>
  <label for="customRange3" class="form-label">Driving Speed: {driveSpeedValue}</label>
  <input type="range" class="form-range" min="-100" max="100" bind:value={driveSpeedValue}>
  <label for="customRange3" class="form-label">Driving Direction: {driveDirectionValue}</label>
  <input type="range" class="form-range" min="-100" max="100" bind:value={driveDirectionValue}>
</Wrapper>

{/if}



