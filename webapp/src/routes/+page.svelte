<script lang="ts">
    import { goto } from "$app/navigation";
    import Wrapper from "./wrapper.svelte";
    import { performConnect, connectionMessage, isConnected, isConnecting, isError } from "$lib/connection.svelte";

    const connectStatusColor = $derived(isError() ? "text-danger" : "text-dark");

    $effect(() => {
        if (isConnected()) goto("/control");
    });
</script>

<Wrapper connectButtonAction={performConnect} connectButtonDisabled={isConnecting()} connectButtonText={"Connect"} statusColor={connectStatusColor} statusText={connectionMessage()}>
    <h1 class="fs-4 card-title fw-bold mb-4 text-center">WALL-E Controller</h1>
    <p class="card-subtitle text-center">Remote Control via the Web Bluetooth API</p>
</Wrapper>