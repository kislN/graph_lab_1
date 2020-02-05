
#ifndef LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
#define LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H

/// Comparator for std::sort.
template <typename T>
bool comp(EDGE<T> a, EDGE<T> b){
    return a.weight < b.weight;
}


/// Radix sort.
template <typename T>
void radix_sort(vector<EDGE<T>> &vec){
    vector<EDGE<T>> output = vec;
    UI vec_size = vec.size();
    unsigned char type_size = sizeof(T);

    for (UI rank = 0; rank < type_size; rank++){
        vector<UI> count(256);
        UI shift = rank * 8;

        for (UI i = 0; i < vec_size; i++)
        {
            count[static_cast<uint8_t>((vec[i].weight & (0xff << shift)) >> shift )]++;
        }

        for (UI i = 1; i < 256; i++)
            count[i] += count[i - 1];

        for (UI i = vec_size; i > 0; i--)
        {
            uint8_t dig = static_cast<uint8_t>((vec[i-1].weight & (0xff << shift)) >> shift );
            output[count[dig] - 1].vertex_a = vec[i-1].vertex_a;
            output[count[dig] - 1].vertex_b = vec[i-1].vertex_b;
            output[count[dig] - 1].weight = vec[i-1].weight;
            count[dig]--;
        }

        for (UI i = 0; i < vec_size; i++) {
            vec[i].vertex_a = output[i].vertex_a;
            vec[i].vertex_b = output[i].vertex_b;
            vec[i].weight = output[i].weight;
        }
    }
}


/// Bucket sort.
template <typename T>
void bucket_sort(vector<EDGE<T>> &vec, const UI &num_buckets)
{
    T min_element = vec[0].weight, max_element = vec[0].weight;
    vector<vector<EDGE<T>>> buckets(num_buckets, vector<EDGE<T>>());

    for (UI i=0; i<vec.size(); i++){
        min_element = min(vec[i].weight, min_element);
        max_element = max(vec[i].weight, max_element);
    }

    T range = max_element - min_element + 1;
    double d = double(num_buckets) / range;

    for (UI i=0; i<vec.size(); i++){
        UI index = UI((vec[i].weight - min_element) * d);
        if (index == num_buckets) index--;
//        UI index = UI((vec[i].weight - min_element)/range);

        buckets[index].push_back(vec[i]);
    }
    for (UI i=0; i < num_buckets; i++){
        sort(buckets[i].begin(), buckets[i].end(), comp<T>);
    }

    vec.clear();

    for (UI i=0; i < num_buckets; i++){
        for (UI j=0; j<buckets[i].size(); j++){
            vec.push_back(buckets[i][j]);
        }
    }
}


#endif //LAB1_GRAPHS_ALGO_WEIGHTS_SORT_H
