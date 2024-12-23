<script lang="ts">
    import { ControlVariable } from "./lib/control.svelte";
    const { name, code, value } : {name: string, code: string, value: number} = $props();
    const sliderControlVariable = new ControlVariable(code, value, (v) => String(Math.floor(v)));
</script>

<label for="range" class="form-label"><strong>{name}:</strong> {sliderControlVariable.value}</label><br>
<input id="range" type="range" class="form-range" min="-100" max="100" bind:value={sliderControlVariable.value}>