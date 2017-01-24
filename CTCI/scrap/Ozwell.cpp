/*
Node := {
   Data
   list<Node>
}
   
Graph := {
   list<Node>
}
*/


struct Node {
    Node(int item) {
        data = item;
    }
    int data;
    std::vector<Node*> adjNodes;
};

struct Graph {
    std::vector<Node> nodes;
    
    //O(n)
    Graph(const Graph &original) {
        std::unordered_map<Node*, Node*> corrNodes;
            
        // O(n) runtime
        for (int i = 0; i < original.nodes.size(); i++) {
            nodes.push_back(Node(original.nodes[i].data));
            corrNodes.insert(original.nodes[i], nodes[i]);
        }
        
        // M : number of connections
        // O(M)
        for (int i = 0; i < original.nodes.size(); i++) {
            for (int j = 0; j < original.nodes[i].adjNodes.size(); j++) {
                nodes[i].adjNodes.push_back(corrNodes[original.nodes[i].adjNodes[j]]);
            }
        }
    }
};



// copy nodes vector
        
        // run thru original->adjNodes
        // figure out index within vector (search)
        // create new vector adjNode
        
        // #2
        // copy nodes vector
        // push_back into corresponding node of original->adjNodes
        // loop thru each original->nodes
            // loop thru each ->adjNodes
            // push adjNode copies into corresponding copy node




// DNUOR 2

// simplify(std::string str)

/*

/../.././//////

//robin/hood/poo/doo/../../../../../..

////////../../robin/hood


*/