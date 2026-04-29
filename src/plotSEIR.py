import pandas as pd
import matplotlib.pyplot as plt #librarys

#load csv in
data = pd.read_csv("SEIRrecord.csv")
data.columns = data.columns.str.strip() #removes spaces from header titles

#SEIR vs time
plt.plot(data["t"], data["S"], label="Susceptible")
plt.plot(data["t"], data["E"], label="Exposed")
plt.plot(data["t"], data["I"], label="Infected")
plt.plot(data["t"], data["R"], label="Recovered")

#plot customisation
plt.xlabel("Time step")
plt.ylabel("Number of people")
plt.title("SEIR Simulation")
plt.legend()
plt.grid()

#displays the plot
plt.show()
