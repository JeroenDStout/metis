# %matplotlib widget

import lab_helper
lab_helper.import_metis_pyd()
from lab_helper import metis_py as metis

# +
print(metis.get_version())

reps = 0
# -
my_set = metis.set()


# +
subject = my_set.add_subject()

view = my_set.add_query()
view.question = "my question"
view.answer   = "my answer"
print(view.get_dbg_string())
# -

print(my_set.get_stats_string())
