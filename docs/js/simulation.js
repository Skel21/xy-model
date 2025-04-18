let isPaused = false;
const playPauseButton = $("#play-pause-button");
const temperatureInput = $("#temperature");
const temperatureOutput = $("#temperature-output");
const anisotropyInput = $("#anisotropy");
const anisotropyOutput = $("#anisotropy-output");
const externalFieldInput = $("#external-field");
const externalFieldOutput = $("#external-field-output");

function reset() {
    Module.reset();
}

function set_temperature(temperature) {
    temperatureOutput.text(temperature);
    Module.set_temperature(parseFloat(temperature));
}

function set_anisotropy(anisotropy) {
    anisotropyOutput.text(anisotropy);
    Module.set_anisotropy(parseFloat(anisotropy));
}

function set_external_field(external_field) {
    externalFieldOutput.text(external_field);
    Module.set_external_field(parseFloat(external_field));
}

function play_pause() {
    isPaused = !isPaused;
    playPauseButton.text(isPaused ? "play_arrow" : "pause");
    Module.play_pause(isPaused);
}

Module.onRuntimeInitialized = () => {
    console.log("WASM Module Loaded");
    Module.init();
    temperatureInput.value = "1.0";
    anisotropyInput.value = "0.0";
    externalFieldInput.value = "0.0";
    set_temperature("1.0");
    set_anisotropy("0.0");
    set_external_field("0.0");
    Module.set_main_loop();
}