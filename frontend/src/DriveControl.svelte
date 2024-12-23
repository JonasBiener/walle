<script lang="ts">
    import { JoyStick } from "./lib/joy"
    import { ControlVariable } from "./lib/control.svelte";
    import { onMount } from "svelte";
    const speedControlVariable = new ControlVariable("DSPEED", 0, (v) => String(Math.floor(v)));
    const directionControlVariable = new ControlVariable("DDIREC", 0, (v) => String(Math.floor(v)));

    onMount(() => {
        new JoyStick('joyDiv', {
            internalFillColor: "#0d6efd",
            internalLineWidth: 2,
            internalStrokeColor: "#0d6efd",
            externalLineWidth: 2,
            externalStrokeColor: "black",
            autoReturnToCenter: true
            }, (stickData: any) => {
                speedControlVariable.value = stickData.y;
                directionControlVariable.value = stickData.x;
            }
        );
    });

</script>

<div style="width: 100%; display: inline-block; text-align: center;">
    <div id="joyDiv" style="display: inline-block; height: 200px; width: 200px;"></div>
</div>

<!--
<label for="range" class="form-label">
    <strong>Driving Speed:</strong> {speedControlVariable.value} 
    <strong> Driving Direction:</strong> {directionControlVariable.value}
</label><br>
-->