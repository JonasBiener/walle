<script lang="ts">
    import { goto } from "$app/navigation";
    import Wrapper from "../wrapper.svelte";
    import { performDisconnect, isConnected } from "$lib/connection.svelte";

    let driveSpeedValue = $state(0);
    let driveDirectionValue = $state(0);

    $effect(() => {
        if (!isConnected()) goto("/");
    });
</script>

<Wrapper connectButtonAction={performDisconnect} connectButtonDisabled={false} connectButtonText={"Disconnect"} statusColor={"text-success"} statusText={"Connected"}>
    <label for="customRange3" class="form-label">Driving Speed: {driveSpeedValue}</label>
    <input type="range" class="form-range" min="-100" max="100" bind:value={driveSpeedValue}>
    <label for="customRange3" class="form-label">Driving Direction: {driveDirectionValue}</label>
    <input type="range" class="form-range" min="-100" max="100" bind:value={driveDirectionValue}>
</Wrapper>