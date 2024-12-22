import * as bluetooth from "./bluetooth"

let isConnectedState = $state(false);
export const isConnected = () => isConnectedState;
let isConnectingState = $state(false);
export const isConnecting = () => isConnectingState;
let isErrorState = $state(false);
export const isError = () => isErrorState;
let connectionMessageState = $state("Disconnected");
export const connectionMessage = () => connectionMessageState;


isConnectedState = JSON.parse(sessionStorage.getItem("isConnected") || "{}");
isErrorState = JSON.parse(sessionStorage.getItem("isError") || "{}");


export async function performConnect(): Promise<void> {
    try {
        sessionStorage.setItem("isConnected", JSON.stringify(false));
        sessionStorage.setItem("isError", JSON.stringify(false));
        isConnectedState = false;
        isConnectingState = true;
        isErrorState = false;
        connectionMessageState = "Discovering";
        //await bluetooth.discoverBLE();
        await new Promise(r => setTimeout(r, 500));
        connectionMessageState = "Connecting";
        //await bluetooth.connectBLE();
        await new Promise(r => setTimeout(r, 500));
        connectionMessageState = "Establishing";
        //await bluetooth.discoverServicesAndCharacteristicsBLE();
        await new Promise(r => setTimeout(r, 500));
        isConnectedState = true;
        isConnectingState = false;
        connectionMessageState = "Connected";
        sessionStorage.setItem("isConnected", JSON.stringify(true));
    } catch (error: any) {
        isConnectedState = false;
        isConnectingState = false;
        isErrorState = true;
        connectionMessageState = error.message;
        sessionStorage.setItem("isError", JSON.stringify(true));
    }
}

export async function performDisconnect(): Promise<void> {
    // await bluetooth.disconnectBLE();
    await new Promise(r => setTimeout(r, 500));
    isConnectedState = false;
    isConnectingState = false;
    connectionMessageState = "Disconnected";
    sessionStorage.setItem("isConnected", JSON.stringify(false));
}