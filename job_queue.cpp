#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct WorkerKey {
	WorkerKey(int _worker, int _next_free_time) :
		worker(_worker),
		free_time(_next_free_time) {}

	bool operator<(const WorkerKey &rhs) const {
		if (free_time > rhs.free_time) return true;
		if (free_time < rhs.free_time) return false;

		if (worker > rhs.worker) return true;
		if (worker < rhs.worker) return false;

		return false;
	}

	int		worker;
	long long	free_time;
};

class JobQueue {
	private:
		int num_workers_;
		vector<int> jobs_;

		vector<int> assigned_workers_;
		vector<long long> start_times_;

		void WriteResponse() const {
			for (int i = 0; i < jobs_.size(); ++i) {
				cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
			}
		}

		void ReadData() {
			int m;
			cin >> num_workers_ >> m;
			jobs_.resize(m);
			for(int i = 0; i < m; ++i) {
				cin >> jobs_[i];
			}
		}

		void AssignJobs() {
			assigned_workers_.resize(jobs_.size());
			start_times_.resize(jobs_.size());
			vector<long long> next_free_time(num_workers_, 0);
			priority_queue<WorkerKey> workers_queue;

			for (int i = 0; i < num_workers_; i++) {
				workers_queue.push(WorkerKey(i, 0));
			}

			for (int i = 0; i < jobs_.size(); ++i) {
				int duration = jobs_[i];
				WorkerKey worker_key = workers_queue.top();

				workers_queue.pop();

				assigned_workers_[i] = worker_key.worker;
				start_times_[i] = worker_key.free_time;

				worker_key.free_time += duration;
				workers_queue.push(worker_key);
			}
		}

	public:
		void Solve() {
			ReadData();
			AssignJobs();
			WriteResponse();
		}
};

int main()
{
	ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}
