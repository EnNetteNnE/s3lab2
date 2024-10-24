#include <iostream>
#include "M.hpp"
#include "SE.hpp"



int main() {
    Set set;
    set.put(4);
    set.put(10);
    set.put(5);
    set.put(1);
    set.put(3);
    set.put(7);

    Vector values = set.values();
    values.sort();
    values.reverse();
   
    Vector<int> val;
    for (int i = 0; i < values.size(); i++) {
        int element = values.get(i);
        val.pushBack(element);
    }

    int gorg = 0;
    for(int i = 2; i < val.size(); i++) {
        if (val.size() % i == 0) {
            //int kol = val.size() / i;

            int sumV = 0;
            for (int j = 0; j < val.size(); j++) {
                sumV += val.get(j);
            }

            if (sumV % i == 0) {
                int sumMinV = sumV / i;
                Vector<Vector<int>> Out;

                for (int k = 0; k < i; k++) {
                    Vector<int> OutMin;
                    Out.pushBack(OutMin);
                }

                for (int j = 0; j < val.size(); j++) {
                    int element = val.get(j);
                    int minSum = 100000;
                    int indexVec = 0;

                    for (int k = 0; k < i; k++) {
                        Vector<int> OutMin = Out.get(k);
                        int sumOutMin = 0;
                        int sumOM = 0;
                        for (int r = 0; r < OutMin.size(); r++) {
                            sumOM += OutMin.get(r);
                        }
                        if (minSum > sumOM) {
                            indexVec = k;
                            minSum = sumOM;
                        }
                    }

                    Vector<int> OutMin0 = Out.get(indexVec);
                    OutMin0.pushBack(element);
                    Out.set(indexVec, OutMin0);
                }

                for (int j = 0; j < Out.size(); j++) {
                    Vector<int> OutMin0 = Out.get(j);
                    cout << "{" << OutMin0 << "}" << " ";
                }
                cout << endl;
            }


        }
    }


    
    
}