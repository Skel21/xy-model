emcc --bind ./cpp/main.cpp -o ./docs/wasm/xy_model.js \
    -s USE_SDL=3 \
    -s ENVIRONMENT='web' \
    -s MODULARIZE=0 \
    -s EXPORT_NAME='XYModel'

cd docs

sass ./scss/materialize.scss ./css/materialize.css

python3 -m http.server 8000 -d .
