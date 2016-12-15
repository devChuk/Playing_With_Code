// This is the text editor interface. 
// Anything you type or change here will be seen by the other person in real time.

// job { start time, end time, job metadata }

// as a function of t, what jobs are running at time t?

// jobsRunning(jobs, t)



std::vector<job> jobsRunning(std::vector<job> jobs, int t) {
    // sort 
    std::sort(jobs.begin(), jobs.end(), /*access jobs.startTime*/);
    
    std::vector<job> result;

    // look through jobs
        // if time t is between the start time and the end time [ ], add it to the result
    for (size_t i = 0; i < jobs.size(); i++) {
        // check if end time is before t
        if (t >= jobs[i].startTime && t <= jobs[i].endTime) {
            result.push_back(jobs[i]);
        } else if (jobs[i].startTime > t)
            break;
    }

    return result;
}