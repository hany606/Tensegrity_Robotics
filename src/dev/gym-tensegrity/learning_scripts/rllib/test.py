import gym
import gym_tensegrity
import ray
from ray import tune

def create_environment(env_config):
    import gym_tensegrity
    return gym.make('gym_tensegrity:jumper-v0')


# Gives errors as env_config is empty but in the documentation it shouldn't
# https://ray.readthedocs.io/en/latest/rllib-env.html#configuring-environments
# class MultiEnvPorts(gym.Env):
#     def __init__(self, env_config):
#         import gym_tensegrity
#         print("----------------------------------------------------------------/**//*/*/")
#         print(env_config)
#         self.config = {'port_num': 1000+env_config.worker_index}
#         self.env = gym.make('gym_tensegrity:jumper-v0', config=self.config)
#     def reset(self):
#         return self.env.reset()
#     def step(self, action):
#         return self.env.step(action)

ray.init()
tune.register_env("Jumper", create_environment)
# tune.register_env("Jumper", lambda config: MultiEnvPorts(config))
analysis = tune.run(
        "ARS",
        name="long_Train",
        stop={
            "timesteps_total": 500000,
        },
        verbose=2,
        reuse_actors= True,
        config={
            "env": "Jumper",
            "num_workers": 1,
            "noise_stdev": 0.02,
            "num_rollouts": 30,
            "rollouts_used": 30,
            "sgd_stepsize": 0.01,
            "noise_size": 250000000,
            "eval_prob": 0.09,
            # "num_envs_per_worker":1,
        },
    )

# print("*-*-*-*-*--*-**-*-*-*-*-*-*-*-*--*-*---*--*-*-*-*-*--*-*--*-*-*--*-")
# for i in analysis.trials:
#     print(i)
# # print(analysis.trials)
# print("*-*-*-*-*--*-**-*-*-*-*-*-*-*-*--*-*---*--*-*-*-*-*--*-*--*-*-*--*-")