# python module for camera model

```bash
# 1.install pybind11
pip install "pybind11[global]"
# 2. enable python build
# set PYTHON_VERSION in python/camera_model/CMakeLists.txt
# 3. build dynamic lib
./compile.sh  -c linux install
# 4. install  python package 
pip install -v .
# 5. run example
python python/example.py
```

## 直接安装python模块 
目前仅支持python3.8, 3.10, 3.11
```bash 
pip install git+ssh://git@github.com/nreal-alg-ai/camera_model_py.git 
```