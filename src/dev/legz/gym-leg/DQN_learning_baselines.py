#using stable-baselines
import gym_roboticArm

import gym
from gym import wrappers
import random
import numpy as np
import matplotlib.pyplot as plt

from stable_baselines.common.vec_env import DummyVecEnv
from stable_baselines.deepq.policies import MlpPolicy
from stable_baselines import DQN

env = gym.make('roboticArm-v0')
# env = wrappers.Monitor(env, 'CartPole_q_learning_video', force=True)

env = DummyVecEnv([lambda: env])

model = DQN(MlpPolicy, env, verbose=1)
model.learn(total_timesteps=25000)
model.save("deepq_roboticArm")

del model # remove to demonstrate saving and loading

model = DQN.load("deepq_roboticArm")

obs = env.reset()
while True:
    action, _states = model.predict(obs)
    obs, rewards, dones, info = env.step(action)
    env.render()