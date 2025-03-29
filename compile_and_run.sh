emcc --bind ./cpp/main.cpp -o ./web/wasm/xy_model.js \
    -s USE_SDL=3 \
    -s ENVIRONMENT='web' \
    -s MODULARIZE=0 \
    -s EXPORT_NAME='XYModel'

cd web
python3 -m http.server 8000 -d .
