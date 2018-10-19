/** 
* @defgroup cluster_mem Cluster Memory
* @brief Memory operations on the cluster_t structure.
*/

/**
 * @defgroup cluster_manip Cluster Manipulation
 * @brief Operations manipulating the contents of cluster_t structure.
 */

/**
 * @defgroup gv Global Variables
 * @brief Global variables
 */

/**
 * @defgroup IO_ops Input and Output
 * @brief Operations for input and output of clusters and objects.
 */

/**
 * @defgroup property_det Properties
 * @brief Operations measuring properties of clusters and objects within them.
 */

/**
* @brief Represents an object in space.
*/
struct obj_t {
    int id;		/**< Unique value of an object. */
    float x;		/**< X coordinate of an object. */
    float y;		/**< Y coordinate of an object. */
};

/**
* @brief Represents an array of objects within a cluster.
*/
struct cluster_t {
    int size;		/**< Number of objects currently in cluster. */		
    int capacity;	/**< Capacity of a cluster. */
    struct obj_t *obj;	/**< Array of obj_t objects. */
};

/**
* @addtogroup cluster_mem
* @{
*/

/**
* Initializes cluster_t structure and allocates array of cap
* obj_t objects. If cap equals 0, array pointer set to NULL.
*
* @param c cluster_t structure to be initialized
* @param cap capacity of the cluster_t structure
*/
void init_cluster(struct cluster_t *c, int cap);

/**
* Frees the memory allocated for array of obj_t objects
* within the cluster_t structure, then reinitializes the cluster
* to an empty state.
*
* @param c cluster_t structure to be cleared and reinitialized
*
* @post c = {size = 0, capacity = 0, obj = NULL}
*/
void clear_cluster(struct cluster_t *c);
///@}

/**
 * @addtogroup gv
 * @{
 */
/// Chunk of cluster objects. Value is recommended for reallocation.
extern const int CLUSTER_CHUNK;

///@}

/**
* @addtogroup cluster_mem
* @{
*/

/**
* Resizes the cluster, changes it's capacity to new_cap.
* 
* @param c cluster_t structure to resize to new capacity
* @param new_cap number to increase the cluster capacity to
* @return cluster_t structure with new capacity
*
* @pre c != NULL
* @pre new_cap >= 0
* @post c->capacity = new_cap
* @post if c->capacity >= new_cap, do nothing and return c
*/
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);
///@}

/**
 * @addtogroup cluster_manip
 * @{
 */

/**
* Appends an object to the end of obt_t array within a cluster.
*
* @param c cluster_t structure carrying array of obt_t
* @param obj obt_t object to be added to the array in cluster
* 
* @pre if c->size < c->capacity, add obj to array in cluster
* @pre if c->size = c->capacity, resize the array in cluster and then append
* @post c->size + 1
*/
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
* Merges the contents of 2 clusters into the first cluster.
*
* @param c1 first cluster_t structure
* @param c2 second cluster_t structure
*
* @pre c1 != NULL
* @pre c2 != NULL
* @post sort_cluster(c1)
*/
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
* Removes a cluster from the array of clusters.
*
* @param carr array of cluster_t structures
* @param narr number of clusters in the array
* @param idx index of cluster to be removed from the array
* @return number of clusters in array after removing cluster at position idx
*
* @pre narr > 0
* @pre narr > idx
* @post narr - 1
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx);

///@}

/**
 * @addtogroup property_det
 * @{
 */

/**
* Computes the distance between 2 objects within a single cluster.
*
* @param o1 first obj_t structure
* @param o2 second obj_t structure
* @return floating point number representing the distance between 2 objects
*
* @pre o1 != NULL
* @pre o2 != NULL
*/
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
* Computes the average distance between two clusters.
*
* @param c1 first cluster_t structure
* @param c2 second cluster_t structure
* @return floating point number representing the distance between 2 clusters
*
* @pre c1 != NULL
* @pre c1-> size > 0
* @pre c2 != NULL
* @pre c2-> size > 0
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Finds two closest clusters based on the average distance of each 2 pairs.
 * Pointers c1 and c2 carry the adress of the pair of closest clusters.
 * 
 * @param carr array of cluster_t structures
 * @param narr number of clusters in the array
 * @param c1 pointer for the first cluster
 * @param c2 pointer for the second cluster
 * 
 * @pre narr > 0
 * @post c1 != NULL
 * @post c2 != NULL
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

///@}

/**
 * @addtogroup cluster_manip
 * @{
 */

/**
* Sorts objects within the cluster in ascending order of their ID.
*
* @param c cluster_t structure to have it's objects sorted
*
* @post c is sorted to ascending order of object ID
*/
void sort_cluster(struct cluster_t *c);

///@}

/**
 * @addtogroup IO_ops
 * @{
 */

/**
* Prints contents of cluster_t structure to stdout.
*
* @param c cluster_t structur to be printed out
*/
void print_cluster(struct cluster_t *c);

/**
 * Opens a file from filename and loads the contents.
 * Each line should contain object id and it's coordinates.
 * 
 * @param filename name of the input file containing object data
 * @param arr pointer to an array of clusters
 * @return integer number representing the number of loaded objects
 * 
 * @pre filename != NULL
 * @post arr contains one cluster for each loaded object
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
* Prints out first narr array members of cluster_t structure.
*
* @param carr array of cluster_t structures, print source
* @param narr number of array members to be printed out
* 
*/
void print_clusters(struct cluster_t *carr, int narr);

///@}
