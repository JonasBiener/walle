<script lang="ts">
    import { ControlVariable } from "./lib/control.svelte";
    const { name, code, value } : {name: string, code: string, value: boolean} = $props();
    const sliderControlVariable = new ControlVariable(code, value, (v) => String(v | 0));
</script>

<label for="flexSwitchCheckDefault" class="form-label mt-3"><strong>{name}:</strong> {sliderControlVariable.value ? "On" : "Off"}</label><br>
<input type="radio" class="btn-check" name="switch" value={false} bind:group={sliderControlVariable.value} id="off-button" autocomplete="off" checked>
<label class="btn btn-outline-primary" for="off-button">Off</label>

<input type="radio" class="btn-check" name="switch" value={true} bind:group={sliderControlVariable.value} id="on-button" autocomplete="off">
<label class="btn btn-outline-primary " for="on-button">On</label>


