import matplotlib.pyplot as plt
import os


directory = "./results/basic/"
basic_graph_data = []
hybrid_graph_data = []
for root, dirs, files in os.walk(directory):
    for file in files:
        filepath = os.path.join(root, file)
        # print(filepath)
    
        with open(filepath, "r") as file:
            content = file.read()
            content = content.split()
            basic_graph_data.append(content)
            # print(content)

#plot cpu time vs problem size
for point in basic_graph_data:
    plt.plot(point[3])
    continue
for point in hybrid_graph_data:
    continue

plt.xlabel('Problem Size')
plt.ylabel('CPU Time')
#plot memory usage vs problem size
for point in basic_graph_data:
    continue

plt.xlabel('Problem Size')
plt.ylabel('Memory Usage')
for point in hybrid_graph_data:
    continue


# if __name__ == "__main__":
