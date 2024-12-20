<script lang="ts">
    import { isConnected } from "$lib/connection.svelte";

    let { children } = $props();

    const stateFavicon = $derived(isConnected() ? "/walleActive.ico" : "/walleBox.ico");
    const stateTitle = $derived(isConnected() ? "Active" : "Inactive");
</script>

<svelte:head>
  <link rel="icon" type="image/svg" href="{stateFavicon}?a=1"/>
  <title>WALL-E {stateTitle} - RoCCI e.V.</title>
</svelte:head>

{@render children()}