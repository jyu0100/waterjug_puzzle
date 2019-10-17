/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Jerry Yu, Noah Suttora
 * Date        : 10/8/19
 * Description : Solves the water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
    
    void add_direction(string s) {
		// Pushes a string into vector directions
		directions.push_back(s);
	}

	bool operator==(State s) {
		// Overloading operator that allows for comparison using ==
		return this -> a == s.a && this -> b == s.b;
	}

	void print_directions() {
		// Print the directions
		for (unsigned int i = 0; i < directions.size(); i++) {
			cout << directions[i] << endl;
		}
	}
};

// Create global variables for the cap and goal states
State cap(0,0,0);
State goal(0,0,0);

void set_cap(State c) {
	// Setter for cap
	cap = c;
}
State get_cap() {
	// Getter for cap
	return cap;
}
void set_goal(State g) {
	// Setter for goal
	goal = g;
}
State get_goal() {
	// Getter for goal
	return goal;
}

State pour(State r, int case_num) {
	// Pour function that traverses the search space using the 6 specific states and sets the proper output
	State cap = get_cap();
	State result = r;
	string output = "";
	if (case_num == 1) {
		// Pour from C to A
		if (result.c > 0 && result.a < cap.a) {
			int amount = min(result.c, cap.a - result.a);
			result.a += amount;
			result.c -= amount;
			if (amount == 1) {
				output = "Pour 1 gallon from C to A. " + result.to_string();
			}
			else {
				output = "Pour " + to_string(amount) + " gallons from C to A. " + result.to_string();
			}
		}
	}
	if (case_num == 2) {
		// Pour from B to A
		if (result.b > 0 && result.a < cap.a) {
			int amount = min(result.b, cap.a - result.a);
			result.a += amount;
			result.b -= amount;
			if (amount == 1) {
				output = "Pour 1 gallon from B to A. " + result.to_string();
			}
			else {
				output = "Pour " + to_string(amount) + " gallons from B to A. " + result.to_string();
			}
		}
	}
	if (case_num == 3) {
		// Pour from C to B
		if (result.c > 0 && result.b < cap.b) {
			int amount = min(result.c, cap.b - result.b);
			result.b += amount;
			result.c -= amount;
			if (amount == 1) {
				output = "Pour 1 gallon from C to B. " + result.to_string();
			}
			else {
				output = "Pour " + to_string(amount) + " gallons from C to B. " + result.to_string();
			}
		}
	}
	if (case_num == 4) {
		// Pour from A to B
		if (result.a > 0 && result.b < cap.b) {
			int amount = min(result.a, cap.b - result.b);
			result.b += amount;
			result.a -= amount;
			if (amount == 1) {
				output = "Pour 1 gallon from A to B. " + result.to_string();
			}
			else {
				output = "Pour " + to_string(amount) + " gallons from A to B. " + result.to_string();
			}
		}
	}
	if (case_num == 5) {
		// Pour from B to C
		if (result.b > 0 && result.c < cap.c) {
			int amount = min(result.b, cap.c - result.c);
			result.c += amount;
			result.b -= amount;
			if (amount == 1) {
				output = "Pour 1 gallon from B to C. " + result.to_string();
			}
			else {
				output = "Pour " + to_string(amount) + " gallons from B to C. " + result.to_string();
			}
		}
	}
	if (case_num == 6) {
		// Pour from A to C
		if (result.a > 0 && result.c < cap.c) {
			int amount = min(result.a, cap.c - result.c);
			result.c += amount;
			result.a -= amount;
			if (amount == 1) {
				output = "Pour 1 gallon from A to C. " + result.to_string();
			}
			else {
				output = "Pour " + to_string(amount) + " gallons from A to C. " +  result.to_string();
			}
		}
	}
	result.add_direction(output);
	return result;
}

void bfs(const int cap_a, const int cap_b, const int cap_c) {
	// Uses breadth-first search algorithm with queue implementation to find and display the solution
	queue<State> q;
	bool **visited = new bool*[cap_a + 1];
	for (int i = 0; i < cap_a + 1; ++i) {
		visited[i] = new bool[cap_b + 1];
		fill(visited[i], visited[i] + cap_b + 1, false);
	}
	State initial(0, 0, cap_c);
	visited[initial.a][initial.b] = true;
	q.push(initial);
	State g = get_goal();
	vector<State> next;
	while (!q.empty()) {
		for (int i = 1; i <= 6; i++) {
			if (q.front() == g) {
				cout << "Initial state. " << initial.to_string() << endl;
				q.front().print_directions();
				return;
			}
			next.push_back(pour(q.front(), i));
		}
		for (auto &s: next) {
			if (!(s == q.front())) {
				if (!visited[s.a][s.b]) {
					visited[s.a][s.b] = true;
					q.push(s);
				}
			}
		}
		q.pop();
	}
	delete[] visited;
	cout << "No solution." << endl;
}

int main(int argc, char * const argv[]) {
    if (argc != 7) {
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}

    istringstream is1(argv[1]), is2(argv[2]), is3(argv[3]), is4(argv[4]), is5(argv[5]), is6(argv[6]);
	int capA, capB, capC, goalA, goalB, goalC;
	if (!(is1 >> capA) || capA < 0) {
		cerr << "Error: Invalid capacity '" << is1.str() << "' for jug A." << endl;
		return 1;
	}
    if (!(is2 >> capB) || capB < 0) {
		cerr << "Error: Invalid capacity '" << is2.str() << "' for jug B." << endl;
		return 1;
	}
    if (!(is3 >> capC) || capC < 0) {
		cerr << "Error: Invalid capacity '" << is3.str() << "' for jug C." << endl;
		return 1;
	}
    if (!(is4 >> goalA) || goalA < 0) {
		cerr << "Error: Invalid goal '" << is4.str() << "' for jug A." << endl;
		return 1;
	}
    if (!(is5 >> goalB) || goalB < 0) {
		cerr << "Error: Invalid goal '" << is5.str() << "' for jug B." << endl;
		return 1;
	}
    if (!(is6 >> goalC) || goalC < 0) {
		cerr << "Error: Invalid goal '" << is6.str() << "' for jug C." << endl;
		return 1;
	}
    if (capC == 0) {
		cout << "Error: Invalid capacity '0' for jug C.";
		return 1;
	}
    if (goalA > capA) {
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	}
    if (goalB > capB) {
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
    if (goalC > capC) {
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}
    if (goalA + goalB + goalC != capC) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
    }
    
    State cap(capA, capB, capC);
	State goal(goalA, goalB, goalC);
	set_cap(cap);
	set_goal(goal);
	bfs(cap.a, cap.b, cap.c);
	return 0;
}