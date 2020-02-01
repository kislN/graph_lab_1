
#ifndef LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
#define LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H

template <typename T>
bool comp(EDGE<T> a, EDGE<T> b){
    return a.weight < b.weight;
}

template <typename T>
void radix_alg(vector<EDGE<T>> &vec, vector<EDGE<T>> output){
    UI n = vec.size();
    unsigned char type_size = sizeof(T);
    for (UI i=0; i<type_size; i++){
        vector<UI> count(256);
        UI k = i * 8;
        for (UI j = 0; j < n; j++)
        {
            count[static_cast<uint8_t>((vec[j].weight & (0xff << k)) >> k )]++;
        }

        for (UI j = 1; j < 256; j++)
            count[j] += count[j - 1];

        for (UI j = n; j > 0; j--)
        {
            uint8_t a = static_cast<uint8_t>((vec[j-1].weight & (0xff << k)) >> k );
            output[count[a] - 1].edge_a = vec[j-1].edge_a;
            output[count[a] - 1].edge_b = vec[j-1].edge_b;
            output[count[a] - 1].weight = vec[j-1].weight;
            count[a]--;
        }

        for (UI j = 0; j < n; j++) {
            vec[j].edge_a = output[j].edge_a;
            vec[j].edge_b = output[j].edge_b;
            vec[j].weight = output[j].weight;
        }
    }
}

template <typename T>
void radix_sort(vector<EDGE<T>> &vec){
    radix_alg(vec, vec);
}


template <typename T>
void bucket_sort(vector<EDGE<T>> &vec, const UI &numBuckets)
{
    T minElement, maxElement = vec[0].weight;
    vector<vector<EDGE<T>>> buckets;
    for (UI i=0; i<numBuckets; i++){
        vector<EDGE<T>> v;
        buckets.push_back(v);
    }
    for (UI i=0; i<vec.size(); i++){
        minElement = min(vec[i].weight, minElement);
        maxElement = max(vec[i].weight, maxElement);
    }
    T range = maxElement - minElement + 1;
    double d = double(numBuckets) / range;
    for (UI i=0; i<vec.size(); i++){
        UI index = UI((vec[i].weight - minElement) * d);
        buckets[index].push_back(vec[i]);
    }
    for (UI i=0; i<numBuckets; i++){
        sort(buckets[i].begin(), buckets[i].end(), comp<T>);
    }
    vec.clear();
    for (UI i=0; i<numBuckets; i++){
        for (UI j=0; j<buckets[i].size(); j++){
            vec.push_back(buckets[i][j]);
        }
    }
}

//
//void bucket_sort(vector<UI> * vec, size_t n)
//{
//    // 1) Create n empty buckets
//    vector<UI> b[n];
//
//    // 2) Put array elements in different buckets
//    for (UI i=0; i<n; i++)
//    {
//        UI bi = n*((*vec)[i]/2147483647); // Index in bucket
//        b[bi].push_back((*vec)[i]);
//    }
//
//    // 3) Sort individual buckets
//    for (UI i=0; i<n; i++)
//        sort(b[i].begin(), b[i].end());
//
//    // 4) Concatenate all buckets into arr[]
//    UI index = 0;
//    for (UI i = 0; i < n; i++)
//        for (UI j = 0; j < b[i].size(); j++)
//            (*vec)[index++] = b[i][j];
//}



#endif //LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
