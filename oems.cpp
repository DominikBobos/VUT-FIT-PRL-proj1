/**
 * Subject: PRL
 * Algorithm: Odd-Even Merge Sort (for 8 numbers)
 * Author: Dominik Boboš <xbobos00@stud.fit.vutbr.cz>
 * Ac.year: 2021/2022
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mpi.h>

//CONSTANTS
#define COMM MPI_COMM_WORLD    /// MPI communicator.
#define TAG 0                  /// Tag used for the messages transmission for numbers within the OEMS .
#define MASTER 0               /// Rank of the master process.
#define NUMBERS_FILE "numbers" /// Input file with random 8 numbers.

using namespace std;

/**
 * Shows err message to stderr and terminates the program with macro value EXIT_FAILURE
 */
auto MPI_error() -> void
{
    cerr << "Some error in MPI library call." << endl;
    MPI_Abort(COMM, EXIT_FAILURE);
}

/**
 * The master (id==0) process reads numbers from the input file and prints them to the
 * stdout,
 * Also it sends the numbers to the corresponding first processes (processes 0-3) .
 * @param rank A rank of a process.
 */
auto read_send_numbers(const int rank)
{
    if (rank != MASTER) // we want only use MASTER for reading input and sending initial numbers to processes
    {
        return;
    }

    ifstream numbers(NUMBERS_FILE); // loading input file
    if (!numbers.is_open() || numbers.bad())
    {
        cerr << "Error when reading an input file. Terminating the program." << endl;
        MPI_Abort(COMM, EXIT_FAILURE);
    }

    for (int i = MASTER; !numbers.eof();  i++)  //read number by number and send it to processes 0-3
    {
        const int number = numbers.get();

        if (numbers.eof())
        {
            break;
        }
        else if (i != 0)
        {
            cout << " ";
        }
        cout << number;
        int dst = i % 4;
        if (MPI_Send(&number, 1, MPI_INT, dst, TAG, COMM))
        {
            MPI_error();
        }
    }
    cout << endl;
}


/**
 * The odd-even merge sort algorithm
 * @param rank A rank of a process.
 */
auto oems(const int rank) -> void
{
    int num1, num2; // numbers for each processor to compare
    //the Destination numbers corresponds to table in the Documentation and it means
    // the rank of the destination processor.
    // The same goes for the source rank.
    if (rank == 0)
    {
        MPI_Recv(&num1, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 4, TAG, MPI_COMM_WORLD);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 5, TAG, MPI_COMM_WORLD);
    }
    if (rank == 1)
    {
        MPI_Recv(&num1, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 4, TAG, MPI_COMM_WORLD);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 5, TAG, MPI_COMM_WORLD);
    }
    if (rank == 2)
    {
        MPI_Recv(&num1, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 6, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 7, TAG, COMM);
    }
    if (rank == 3)
    {
        MPI_Recv(&num1, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 6, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 7, TAG, COMM);
    }
    if (rank == 4)
    {
        MPI_Recv(&num1, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 1, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 10, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 8, TAG, COMM);
    }
    if (rank == 5)
    {
        MPI_Recv(&num1, 1, MPI_INT, 0, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 1, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 8, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 13, TAG, COMM);
    }
    if (rank == 6)
    {
        MPI_Recv(&num1, 1, MPI_INT, 2, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 3, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 10, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 9, TAG, COMM);
    }
    if (rank == 7)
    {
        MPI_Recv(&num1, 1, MPI_INT, 2, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 3, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 9, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 13, TAG, COMM);
    }
    if (rank == 8)
    {
        MPI_Recv(&num1, 1, MPI_INT, 4, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 5, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 12, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 11, TAG, COMM);
    }
    if (rank == 9)
    {
        MPI_Recv(&num1, 1, MPI_INT, 6, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 7, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 12, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 11, TAG, COMM);
    }
    if (rank == 10)
    {
        MPI_Recv(&num1, 1, MPI_INT, 4, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 6, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 0, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 14, TAG, COMM);
    }
    if (rank == 11)
    {
        MPI_Recv(&num1, 1, MPI_INT, 8, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 9, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 14, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 18, TAG, COMM);
    }
    if (rank == 12)
    {
        MPI_Recv(&num1, 1, MPI_INT, 8, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 9, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 16, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 15, TAG, COMM);
    }
    if (rank == 13)
    {
        MPI_Recv(&num1, 1, MPI_INT, 5, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 7, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 15, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 0, TAG, COMM);
    }
    if (rank == 14)
    {
        MPI_Recv(&num1, 1, MPI_INT, 10, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 11, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 16, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 17, TAG, COMM);
    }
    if (rank == 15)
    {
        MPI_Recv(&num1, 1, MPI_INT, 12, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 13, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 17, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 18, TAG, COMM);
    }
    if (rank == 16)
    {
        MPI_Recv(&num1, 1, MPI_INT, 14, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 12, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 0, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 0, TAG, COMM);
    }
    if (rank == 17)
    {
        MPI_Recv(&num1, 1, MPI_INT, 14, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 15, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 0, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 0, TAG, COMM);
    }
    if (rank == 18)
    {
        MPI_Recv(&num1, 1, MPI_INT, 11, TAG, COMM, nullptr);
        MPI_Recv(&num2, 1, MPI_INT, 15, TAG, COMM, nullptr);
        MPI_Send(&min(num1, num2), 1, MPI_INT, 0, TAG, COMM);
        MPI_Send(&max(num1, num2), 1, MPI_INT, 0, TAG, COMM);
    }

    int num; // the last processes sends the sorted list of numbers back to the MASTER
    if (rank == 0) 
    {
        for (int i : {10, 16, 16, 17, 17, 18, 18, 13}) 
        {
            MPI_Recv(&num, 1, MPI_INT, i, 0, COMM, nullptr);
            cout << num << endl;
        }
    }
}

/**
 * Main program. Provides initialization of MPI components
 * @param argc
 * @param argv
 * @return
 */
auto main(int argc, char *argv[]) -> int {

    if (MPI_Init(&argc, &argv))
    {
        MPI_error();
    }

    // Get the number of processes
    int world_size;
    if (MPI_Comm_size(MPI_COMM_WORLD, &world_size))
    {
        MPI_error();
    }

    // Get the rank of the process
    int world_rank;
    if (MPI_Comm_rank(MPI_COMM_WORLD, &world_rank))
    {
        MPI_error();
    }

    // get numbers from file and send to processes
    read_send_numbers(world_rank);
    // do odd-even merge sort
    oems(world_rank);

    // Required for correct behaviour
    MPI_Finalize();

    return EXIT_SUCCESS;
}
