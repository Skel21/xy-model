let isPaused = false;
const playPauseButton = $("#play-pause-button");
const temperatureInput = $("#temperature");
const temperatureOutput = $("#temperature-output");

function reset() {
    Module.reset();
}

function set_temperature(temperature) {
    temperatureOutput.text(temperature);
    Module.set_temperature(parseFloat(temperature));
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
    set_temperature("1.0");
    Module.set_main_loop();
}