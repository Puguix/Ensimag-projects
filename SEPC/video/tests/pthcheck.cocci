// Copyright: Grégory Mounié
// Licence: GPLv3+

// lock should be followed by an unlock on the same mutex before the
// end of the function
@nounlock@
pthread_mutex_t M;
@@
* pthread_mutex_lock(& M);
... when != pthread_mutex_unlock(& M)

// unlock should follow a lock on the same mutex in the function
@nolock@
pthread_mutex_t M;
@@
... when != pthread_mutex_lock(& M)
* pthread_mutex_unlock(& M);

// The cond_wait should be done in a while loop
@noif@
pthread_mutex_t M;
pthread_cond_t C;
expression E;
@@
pthread_mutex_lock(& M);
...
(
* if (E) pthread_cond_wait(& C, & M);
|
* if (E) { ... pthread_cond_wait(& C, & M); ... }
)
...
pthread_mutex_unlock(& M);

// the cond_wait should follow a lock on the same mutex
@waitnolockbefore@
pthread_mutex_t M;
pthread_cond_t C;
@@
... when != pthread_mutex_lock(& M);
* pthread_cond_wait(& C, & M);

// the cond_wait should be followed by an unlock on the same mutex
@waitnounlockafter@
pthread_mutex_t M;
pthread_cond_t C;
@@
* pthread_cond_wait(& C, & M);
... when != pthread_mutex_unlock(& M);

// the signal should follow a lock
@signalnolockbefore@
pthread_mutex_t M;
pthread_cond_t C;
@@
... when != pthread_mutex_lock(& M);
* pthread_cond_signal(& C);

// the signal should be followed by an unlock
@signalnounlockafter@
pthread_mutex_t M;
pthread_cond_t C;
@@
* pthread_cond_signal(& C);
... when != pthread_mutex_unlock(& M);

// same lock should not be taken twice
@repetitivelock@
pthread_mutex_t M;
@@
pthread_mutex_lock(& M);
... when != pthread_mutex_unlock(& M);
* pthread_mutex_lock(& M);

// the mutex should not be freed before wait
@unlockbeforewait@
pthread_mutex_t M;
pthread_cond_t C;
@@
* pthread_mutex_unlock(& M);
... when != pthread_mutex_lock(& M);
pthread_cond_wait(&C, &M);

// the mutex should not be taken after the wait
@lockafterwait@
pthread_mutex_t M;
pthread_cond_t C;
@@
pthread_cond_wait(&C, &M);
... when != pthread_mutex_unlock(& M);
* pthread_mutex_lock(& M);

// the wait should be inside a while
// first rule: find cond_wait with  while
@nowhile@
pthread_mutex_t M;
pthread_cond_t C;
expression E;
position p1;
@@
(
 while(E) pthread_cond_wait@p1(&C, &M);
|
 while(E) { ... pthread_cond_wait@p1(&C, &M); ... }
)

// the wait should be inside a while
// second rule: remaining cond_wait are not in a while
@nowhile2@
pthread_mutex_t M;
pthread_cond_t C;
position p2 != nowhile.p1;
@@
* pthread_cond_wait@p2(&C, &M);

