#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <iterator>

using namespace std;

void readfile(std::vector<std::vector<int>> &raw_graph){
    ifstream input;
    input.open("kargerMinCut_test.txt");
    string line;

    while(getline(input, line)){
        istringstream is(line);
        raw_graph.push_back(std::vector<int>(istream_iterator<int>(is), istream_iterator<int>() ));
    }
    input.close();
}

int karger(std::vector<std::vector<int>> raw_graph, int n){
    //Initialize the random variable
    srand(0);
    
    //Make the edge by using the pair vector
    //Counting src->dst and dst->src differently
    std::vector<std::pair<int, int>> edges;
    for (int src = 0; src < raw_graph.size(); src++){
        for (int dst = 1; dst < raw_graph[src].size(); dst++){
            // cout << "src=" << src << ", dst=" << dst << endl;  
            edges.push_back(pair<int, int>(raw_graph[src][0], raw_graph[src][dst] ));
        }
    }

    int num_nodes = raw_graph.size();
    cout << "Num_nodes=" << num_nodes << endl;
    int num_edges = edges.size();
    cout << "Num_edges=" << num_edges << endl;

    // cout << "initial num_edges=" << num_edges << endl;

    while(num_nodes > 2){
        //Choose random pair
        int edgeIndex = rand() % num_edges;
        int src = edges[edgeIndex].first;
        int dst = edges[edgeIndex].second;

        // cout << "random pair=" << src << " " << dst << endl;

        //Contraction
        for (int e=0; e<num_edges; e++){
            int testSrc = edges[e].first;
            int testDst = edges[e].second;

            if (testSrc == dst) { testSrc = edges[e].first = src;}
            if (testDst == dst) { testDst = edges[e].second = src;}

            // Eliminate self loop    
            if (testSrc == testDst){
                // cout  << "before=" << edges[e].first << " "<< edges[e].second << endl;
                edges[e] = edges[num_edges - 1]; // Bring the last element to the location of the deleted element
                // cout  << "after=" << edges[e].first << " "<< edges[e].second << endl;
                num_edges--;
                e--;
            }
        }
        num_nodes--;

        // for ( std::vector<std::vector<int>>::size_type i = 0; i < edges.size(); i++ ){
        //     cout << edges[i].first << ' ' << edges[i].second << endl;
        // }
    }



    // cout << "num_edges=" << num_edges/2 << endl;

    return num_edges/2;
    // cout << "min_cut_temp:" << min_cut/2 << endl; 
    // return min_cut/2;
    // if (num_edges<min_cut){
    //     min_cut = num_edges;
    // }
    // return min_cut/2;
}

float percent(int i, int iteration_n){
    float i_f = i;
    float iter_f = iteration_n;
    float output = i_f/iter_f * 100.0;
    return output;
}

int karger_repeat(std::vector<std::vector<int>> raw_graph, int n){
    int iteration_n = 10000;//n*n*log2(n);
    int min_cut = raw_graph.size();//n*(n-1)/2;
    for (int i=0; i < iteration_n; i++){
        // cout << "Try: " << i << endl;
        cout << percent(i, iteration_n) << "Percentage Done!" <<endl;
        int num_edges = karger(raw_graph, n);
        min_cut = min(min_cut, num_edges); 
    }
    return min_cut;
}

int main(){
    std::vector<std::vector<int>> raw_graph;

    // read input file
    readfile(raw_graph);
    
    // for ( std::vector<std::vector<int>>::size_type i = 0; i < raw_graph.size(); i++ ){
    // for ( std::vector<int>::size_type j = 0; j < raw_graph[i].size(); j++ ){
    //     cout << raw_graph[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // Get the number of the vertices
    int n = raw_graph.size();
    // run repeated karger
    int min_cut = karger_repeat(raw_graph, n);

    cout << "Min cut = "<< min_cut << endl;
    return 0;
}