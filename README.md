# Sound-Data-Extracts

## Steps
**You should change the data path in the codes!!!**
```
python normailze.py
g++ BS.cpp -o BS.out
./BS.out
cd kalman-cpp/build
make
./kalman-test
cd ../../
python plot_kalman.py
```

## Steps explanation
* Use normalize.py to normalize data.
* Compile and run BS.cpp to find the best shift number for two data.
* Build and run the code in directory "kalman-cpp", if you want to change the output, you can edit kalman-test.cpp and do re-build.
* Run plot_kalman.py to see the output of kalman filter.
