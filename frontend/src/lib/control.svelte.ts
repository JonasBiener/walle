import { sendControl } from "./connection.svelte";

export class ControlVariable {
    value: any = $state();
    constructor (public name: string, public initValue: any, public serializer: (v: any) => string) {
        this.name = name;
        this.value = initValue;
        this.serializer = serializer;
        $effect(() => {
            sendControl(this.name, this.serializer(this.value));
        });
    }
}