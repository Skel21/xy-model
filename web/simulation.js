function reset() {
    Module.reset();
}

function set_temperature(temperature) {
    $("#temperature-output").text(temperature);
    Module.set_temperature(parseFloat(temperature));
}

Module.onRuntimeInitialized = () => {
    console.log("WASM Module Loaded");
    Module.init();
    Module.set_main_loop();
}