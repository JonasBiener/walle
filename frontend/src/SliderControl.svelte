<script lang="ts">
    import { ControlVariable } from "./lib/control.svelte";
    const { name, code, value, min, max } : {name: string, code: string, value: number, min: number, max: number} = $props();
    const sliderControlVariable = new ControlVariable(code, value, (v) => String(Math.floor(v)));
</script>

<label for="range" class="form-label mt-3"><strong>{name}:</strong> {sliderControlVariable.value}</label><br>
<input id="range" type="range" class="form-range" min={min} max={max} bind:value={sliderControlVariable.value}>