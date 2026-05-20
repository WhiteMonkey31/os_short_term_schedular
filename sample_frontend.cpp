#include "sample_frontend.hpp"
#include "sample_backend.hpp"

#include "include/SFML/Graphics.hpp"
#include <iostream>
#include <sstream>

void drawText(
    sf::RenderWindow& window,
    sf::Font& font,
    const std::string& str,
    int size,
    float x,
    float y
) {
    sf::Text t(font, str, size);

    t.setPosition({x, y});

    window.draw(t);
}

void launch_frontend()
{
    sf::RenderWindow window(
        sf::VideoMode({1200, 700}),
        "OS Scheduler Simulator"
    );

    sf::Font font;

    if (!font.openFromFile("assets/sample_arial.ttf")) {

        std::cout << "Font not found\n";
        return;
    }

    std::vector<process> processes;

    int selectedAlgorithm = 0;

    bool simulationDone = false;

    // Sample Input
    processes.push_back({0,3,3,2});
    processes.push_back({1,4,1,5});
    processes.push_back({2,2,2,3});
    processes.push_back({3,0,4,1});
    processes.push_back({4,1,5,4});

    while (window.isOpen()) {

    while (const std::optional event =
        window.pollEvent())
    {
        // Close Window
        if (event->is<sf::Event::Closed>()) {

            window.close();
        }

        // Keyboard Input
        if (const auto* keyPressed =
            event->getIf<sf::Event::KeyPressed>())
        {
            // FCFS
            if (keyPressed->code ==
                sf::Keyboard::Key::Num1)
            {
                selectedAlgorithm = 1;
            }

            // Non Preemptive SJF
            else if (keyPressed->code ==
                    sf::Keyboard::Key::Num2)
            {
                selectedAlgorithm = 2;
            }

            // Preemptive SJF
            else if (keyPressed->code ==
                    sf::Keyboard::Key::Num3)
            {
                selectedAlgorithm = 3;
            }

            // Round Robin
            else if (keyPressed->code ==
                    sf::Keyboard::Key::Num4)
            {
                selectedAlgorithm = 4;
            }

            // Priority Non Preemptive
            else if (keyPressed->code ==
                    sf::Keyboard::Key::Num5)
            {
                selectedAlgorithm = 5;
            }

            // Priority Preemptive
            else if (keyPressed->code ==
                    sf::Keyboard::Key::Num6)
            {
                selectedAlgorithm = 6;
            }

            // ENTER
            else if (keyPressed->code ==
                    sf::Keyboard::Key::Enter)
            {
                initialize_processes_for_preemtive(processes);

                if (selectedAlgorithm == 1) {

                    std::queue<int> rq;

                    fill_readyqueue_non_preemtive_fcfs(
                        processes,
                        rq
                    );

                    executing_readyqueue_fcfs(
                        processes,
                        rq
                    );
                }

                else if (selectedAlgorithm == 2) {

                    std::queue<int> rq;

                    fill_readyqueue_non_preemtive_sjf(
                        processes,
                        rq
                    );

                    executing_readyqueue_fcfs(
                        processes,
                        rq
                    );
                }

                else if (selectedAlgorithm == 3) {

                    execute_preemptive_sjf(processes);
                }

                else if (selectedAlgorithm == 4) {

                    execute_round_robin(processes);
                }

                else if (selectedAlgorithm == 5) {

                    execute_priority_non_preemptive(
                        processes
                    );
                }

                else if (selectedAlgorithm == 6) {

                    execute_priority_preemptive(
                        processes
                    );
                }

                calculate_TT_WT_RT(processes);

                simulationDone = true;
            }
        }
    }

    window.clear(sf::Color(30, 30, 30));

    drawText(window, font,
        "OS Scheduler Simulator",
        36,
        350,
        20
    );

    drawText(window, font,
        "Choose Algorithm:",
        24,
        40,
        100
    );

    drawText(window, font,
        "1 - FCFS",
        22,
        60,
        150
    );

    drawText(window, font,
        "2 - Non Preemptive SJF",
        22,
        60,
        190
    );

    drawText(window, font,
        "3 - Preemptive SJF",
        22,
        60,
        230
    );

    drawText(window, font,
        "4 - Round Robin",
        22,
        60,
        270
    );

    drawText(window, font,
        "5 - Priority Non Preemptive",
        22,
        60,
        310
    );

    drawText(window, font,
        "6 - Priority Preemptive",
        22,
        60,
        350
    );

    drawText(window, font,
        "Press ENTER to Run",
        24,
        60,
        430
    );

    std::string algoName = "None";

    if (selectedAlgorithm == 1)
        algoName = "FCFS";

    else if (selectedAlgorithm == 2)
        algoName = "Non Preemptive SJF";

    else if (selectedAlgorithm == 3)
        algoName = "Preemptive SJF";

    else if (selectedAlgorithm == 4)
        algoName = "Round Robin";

    else if (selectedAlgorithm == 5)
        algoName = "Priority Non Preemptive";

    else if (selectedAlgorithm == 6)
        algoName = "Priority Preemptive";

    drawText(window, font,
        "Selected: " + algoName,
        24,
        500,
        120
    );

    // Display Result Table
    if (simulationDone) {

        drawText(window, font,
            "Results",
            28,
            500,
            180
        );

        drawText(window, font,
            "PID   AT   BT   P   WT   TT   RT   CT",
            20,
            500,
            230
        );

        int y = 270;

        for (const process &p : processes) {

            std::stringstream ss;

            ss
            << p.pID << "      "
            << p.AT << "      "
            << p.BT << "      "
            << p.P << "      "
            << p.WT << "      "
            << p.TT << "      "
            << p.RT << "      "
            << p.CT;

            drawText(window, font,
                ss.str(),
                18,
                500,
                y
            );

            y += 40;
        }
    }

    window.display();
}


        window.clear(sf::Color(30, 30, 30));

        drawText(window, font,
            "OS Scheduler Simulator",
            36,
            350,
            20
        );

        drawText(window, font,
            "Choose Algorithm:",
            24,
            40,
            100
        );

        drawText(window, font,
            "1 - FCFS",
            22,
            60,
            150
        );

        drawText(window, font,
            "2 - Non Preemptive SJF",
            22,
            60,
            190
        );

        drawText(window, font,
            "3 - Preemptive SJF",
            22,
            60,
            230
        );

        drawText(window, font,
            "4 - Round Robin",
            22,
            60,
            270
        );

        drawText(window, font,
            "5 - Priority Non Preemptive",
            22,
            60,
            310
        );

        drawText(window, font,
            "6 - Priority Preemptive",
            22,
            60,
            350
        );

        drawText(window, font,
            "Press ENTER to Run",
            24,
            60,
            430
        );

        std::string algoName = "None";

        if (selectedAlgorithm == 1)
            algoName = "FCFS";

        else if (selectedAlgorithm == 2)
            algoName = "Non Preemptive SJF";

        else if (selectedAlgorithm == 3)
            algoName = "Preemptive SJF";

        else if (selectedAlgorithm == 4)
            algoName = "Round Robin";

        else if (selectedAlgorithm == 5)
            algoName = "Priority Non Preemptive";

        else if (selectedAlgorithm == 6)
            algoName = "Priority Preemptive";

        drawText(window, font,
            "Selected: " + algoName,
            24,
            500,
            120
        );

        // Display Result Table
        if (simulationDone) {

            drawText(window, font,
                "Results",
                28,
                500,
                180
            );

            drawText(window, font,
                "PID   AT   BT   P   WT   TT   RT   CT",
                20,
                500,
                230
            );

            int y = 270;

            for (const process &p : processes) {

                std::stringstream ss;

                ss
                << p.pID << "      "
                << p.AT << "      "
                << p.BT << "      "
                << p.P << "      "
                << p.WT << "      "
                << p.TT << "      "
                << p.RT << "      "
                << p.CT;

                drawText(window, font,
                    ss.str(),
                    18,
                    500,
                    y
                );

                y += 40;
            }
        }

        window.display();
    }
