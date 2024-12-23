<script lang="ts">
  import Wrapper from "./wrapper.svelte";
  import SliderControl from "./SliderControl.svelte";
  import SwitchControl from "./SwitchControl.svelte";
  import { activateConnection, deactivateConnection, isConnected } from "./lib/connection.svelte";
</script>

<Wrapper 
  connectButtonAction={!isConnected() ? activateConnection : deactivateConnection} 
  connectButtonText={!isConnected() ? "Activate" : "Deactivate"} 
  statusColor={!isConnected() ? "text-danger" : "text-success"} 
  statusText={!isConnected() ? "Inactive" : "Active"} 
  favicon={!isConnected() ? "/walleBox.ico" : "/walleActive.ico"}>

  {#if !isConnected()}

  <h1 class="fs-4 card-title fw-bold mb-4 text-center">WALL-E Controller</h1>
  <p class="card-subtitle text-center">Remote Control using WebSockets</p>

  {:else}

  <SliderControl code={"DSPEED"} name={"Driving Speed"} value={0}></SliderControl>
  <SliderControl code={"DDIREC"} name={"Driving Direction"} value={0}></SliderControl>
  <SwitchControl code={"DINVRT"} name={"Invert Driving"} value={false}></SwitchControl>

  {/if}

</Wrapper>