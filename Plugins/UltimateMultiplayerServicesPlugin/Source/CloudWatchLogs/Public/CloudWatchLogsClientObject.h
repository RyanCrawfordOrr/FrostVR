/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#include "Auth/AWSCoreCredentials.h"
#include "Client/AWSClientConfiguration.h"

#include "CloudWatchLogsError.h"

#include "Model/AssociateKmsKeyRequest.h"
#include "Model/CancelExportTaskRequest.h"
#include "Model/CreateExportTaskRequest.h"
#include "Model/CreateLogGroupRequest.h"
#include "Model/CreateLogStreamRequest.h"
#include "Model/AWSCloudWatchLogsDeleteDataProtectionPolicyRequest.h"
#include "Model/DeleteDestinationRequest.h"
#include "Model/DeleteLogGroupRequest.h"
#include "Model/DeleteLogStreamRequest.h"
#include "Model/DeleteMetricFilterRequest.h"
#include "Model/DeleteQueryDefinitionRequest.h"
#include "Model/DeleteResourcePolicyRequest.h"
#include "Model/DeleteRetentionPolicyRequest.h"
#include "Model/DeleteSubscriptionFilterRequest.h"
#include "Model/DescribeDestinationsRequest.h"
#include "Model/DescribeExportTasksRequest.h"
#include "Model/DescribeLogGroupsRequest.h"
#include "Model/DescribeLogStreamsRequest.h"
#include "Model/DescribeMetricFiltersRequest.h"
#include "Model/DescribeQueriesRequest.h"
#include "Model/DescribeQueryDefinitionsRequest.h"
#include "Model/DescribeResourcePoliciesRequest.h"
#include "Model/DescribeSubscriptionFiltersRequest.h"
#include "Model/DisassociateKmsKeyRequest.h"
#include "Model/FilterLogEventsRequest.h"
#include "Model/AWSCloudWatchLogsGetDataProtectionPolicyRequest.h"
#include "Model/GetLogEventsRequest.h"
#include "Model/GetLogGroupFieldsRequest.h"
#include "Model/GetLogRecordRequest.h"
#include "Model/GetQueryResultsRequest.h"
#include "Model/AWSCloudWatchLogsListTagsForResourceRequest.h"
#include "Model/AWSCloudWatchLogsPutDataProtectionPolicyRequest.h"
#include "Model/PutDestinationRequest.h"
#include "Model/PutDestinationPolicyRequest.h"
#include "Model/PutLogEventsRequest.h"
#include "Model/PutMetricFilterRequest.h"
#include "Model/PutQueryDefinitionRequest.h"
#include "Model/PutResourcePolicyRequest.h"
#include "Model/PutRetentionPolicyRequest.h"
#include "Model/PutSubscriptionFilterRequest.h"
#include "Model/StartQueryRequest.h"
#include "Model/StopQueryRequest.h"
#include "Model/AWSCloudWatchLogsTagResourceRequest.h"
#include "Model/TestMetricFilterRequest.h"
#include "Model/AWSCloudWatchLogsUntagResourceRequest.h"

#include "Model/CreateExportTaskResult.h"
#include "Model/DeleteQueryDefinitionResult.h"
#include "Model/DescribeDestinationsResult.h"
#include "Model/DescribeExportTasksResult.h"
#include "Model/DescribeLogGroupsResult.h"
#include "Model/DescribeLogStreamsResult.h"
#include "Model/DescribeMetricFiltersResult.h"
#include "Model/DescribeQueriesResult.h"
#include "Model/DescribeQueryDefinitionsResult.h"
#include "Model/DescribeResourcePoliciesResult.h"
#include "Model/DescribeSubscriptionFiltersResult.h"
#include "Model/FilterLogEventsResult.h"
#include "Model/AWSCloudWatchLogsGetDataProtectionPolicyResult.h"
#include "Model/GetLogEventsResult.h"
#include "Model/GetLogGroupFieldsResult.h"
#include "Model/GetLogRecordResult.h"
#include "Model/GetQueryResultsResult.h"
#include "Model/AWSCloudWatchLogsListTagsForResourceResult.h"
#include "Model/AWSCloudWatchLogsPutDataProtectionPolicyResult.h"
#include "Model/PutDestinationResult.h"
#include "Model/PutLogEventsResult.h"
#include "Model/PutQueryDefinitionResult.h"
#include "Model/PutResourcePolicyResult.h"
#include "Model/StartQueryResult.h"
#include "Model/StopQueryResult.h"
#include "Model/TestMetricFilterResult.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/CloudWatchLogsClient.h"

#endif

#include "CloudWatchLogsClientObject.generated.h"

/**
*  <p>You can use Amazon CloudWatch Logs to monitor, store, and access your log files from EC2 instances, AWS CloudTrail, or other sources. You can then retrieve the associated log data from CloudWatch Logs using the CloudWatch console, CloudWatch Logs commands in the AWS CLI, CloudWatch Logs API, or CloudWatch Logs SDK.</p> <p>You can use CloudWatch Logs to:</p> <ul> <li> <p> <b>Monitor logs from EC2 instances in real-time</b>: You can use CloudWatch Logs to monitor applications and systems using log data. For example, CloudWatch Logs can track the number of errors that occur in your application logs and send you a notification whenever the rate of errors exceeds a threshold that you specify. CloudWatch Logs uses your log data for monitoring so no code changes are required. For example, you can monitor application logs for specific literal terms (such as "NullReferenceException") or count the number of occurrences of a literal term at a particular position in log data (such as "404" status codes in an Apache access log). When the term you are searching for is found, CloudWatch Logs reports the data to a CloudWatch metric that you specify.</p> </li> <li> <p> <b>Monitor AWS CloudTrail logged events</b>: You can create alarms in CloudWatch and receive notifications of particular API activity as captured by CloudTrail. You can use the notification to perform troubleshooting.</p> </li> <li> <p> <b>Archive log data</b>: You can use CloudWatch Logs to store your log data in highly durable storage. You can change the log retention setting so that any log events older than this setting are automatically deleted. The CloudWatch Logs agent makes it easy to quickly send both rotated and non-rotated log data off of a host and into the log service. You can then access the raw log data when you need it.</p> </li> </ul>
**/
UCLASS(BlueprintType)
class CLOUDWATCHLOGS_API UCloudWatchLogsClientObject : public UObject {
    GENERATED_BODY()

public:
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    Aws::CloudWatchLogs::CloudWatchLogsClient *awsCloudWatchLogsClient;
#endif

    /**
    * public static UCloudWatchLogsClientObject::CreateCloudWatchLogsObject
    * Creates a CloudWatchLogsObject. This function must be called first before accessing any CloudWatchLogs client functions.
    * @param credentials [FAWSCredentials] .
    * @param clientConfiguration [FClientConfiguration] .
    * @return [UCloudWatchLogsClientObject*] Returns UCloudWatchLogsClientObject*.
    **/
    UFUNCTION(BlueprintCallable, Category = "CloudWatchLogs Client")
    static UCloudWatchLogsClientObject *
    CreateCloudWatchLogsObject(const FAWSCredentials &credentials, const FAWSClientConfiguration &clientConfiguration);

    /**
    * <p>Associates the specified KMS key with the specified log group.</p> <p>Associating a KMS key with a log group overrides any existing associations between the log group and a KMS key. After a KMS key is associated with a log group, all newly ingested data for the log group is encrypted using the KMS key. This association is stored as long as the data encrypted with the KMS keyis still within CloudWatch Logs. This enables CloudWatch Logs to decrypt this data whenever it is requested.</p> <important> <p>CloudWatch Logs supports only symmetric KMS keys. Do not use an associate an asymmetric KMS key with your log group. For more information, see <a href="https://docs.aws.amazon.com/kms/latest/developerguide/symmetric-asymmetric.html">Using Symmetric and Asymmetric Keys</a>.</p> </important> <p>It can take up to 5 minutes for this operation to take effect.</p> <p>If you attempt to associate a KMS key with a log group but the KMS key does not exist or the KMS key is disabled, you receive an <code>InvalidParameterException</code> error. </p>
    * @param
    * @param associateKmsKeyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void AssociateKmsKey (
        UObject *WorldContextObject,
        bool &success,
        FAssociateKmsKeyRequest associateKmsKeyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Cancels the specified export task.</p> <p>The task must be in the <code>PENDING</code> or <code>RUNNING</code> state.</p>
    * @param
    * @param cancelExportTaskRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void CancelExportTask (
        UObject *WorldContextObject,
        bool &success,
        FCancelExportTaskRequest cancelExportTaskRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates an export task so that you can efficiently export data from a log group to an Amazon S3 bucket. When you perform a <code>CreateExportTask</code> operation, you must use credentials that have permission to write to the S3 bucket that you specify as the destination.</p> <p>Exporting log data to S3 buckets that are encrypted by KMS is supported. Exporting log data to Amazon S3 buckets that have S3 Object Lock enabled with a retention period is also supported.</p> <p>Exporting to S3 buckets that are encrypted with AES-256 is supported. </p> <p>This is an asynchronous call. If all the required information is provided, this operation initiates an export task and responds with the ID of the task. After the task has started, you can use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_DescribeExportTasks.html">DescribeExportTasks</a> to get the status of the export task. Each account can only have one active (<code>RUNNING</code> or <code>PENDING</code>) export task at a time. To cancel an export task, use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_CancelExportTask.html">CancelExportTask</a>.</p> <p>You can export logs from multiple log groups or multiple time ranges to the same S3 bucket. To separate log data for each export task, specify a prefix to be used as the Amazon S3 key prefix for all exported objects.</p> <note> <p>Time-based sorting on chunks of log data inside an exported file is not guaranteed. You can sort the exported log field data by using Linux utilities.</p> </note>
    * @param
    * @param createExportTaskRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void CreateExportTask (
        UObject *WorldContextObject,
        bool &success,
        FCreateExportTaskRequest createExportTaskRequest,
        FCreateExportTaskResult &createExportTaskResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates a log group with the specified name. You can create up to 20,000 log groups per account.</p> <p>You must use the following guidelines when naming a log group:</p> <ul> <li> <p>Log group names must be unique within a Region for an Amazon Web Services account.</p> </li> <li> <p>Log group names can be between 1 and 512 characters long.</p> </li> <li> <p>Log group names consist of the following characters: a-z, A-Z, 0-9, '_' (underscore), '-' (hyphen), '/' (forward slash), '.' (period), and '#' (number sign)</p> </li> </ul> <p>When you create a log group, by default the log events in the log group do not expire. To set a retention policy so that events expire and are deleted after a specified time, use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutRetentionPolicy.html">PutRetentionPolicy</a>.</p> <p>If you associate an KMS key with the log group, ingested data is encrypted using the KMS key. This association is stored as long as the data encrypted with the KMS key is still within CloudWatch Logs. This enables CloudWatch Logs to decrypt this data whenever it is requested.</p> <p>If you attempt to associate a KMS key with the log group but the KMS keydoes not exist or the KMS key is disabled, you receive an <code>InvalidParameterException</code> error. </p> <important> <p>CloudWatch Logs supports only symmetric KMS keys. Do not associate an asymmetric KMS key with your log group. For more information, see <a href="https://docs.aws.amazon.com/kms/latest/developerguide/symmetric-asymmetric.html">Using Symmetric and Asymmetric Keys</a>.</p> </important>
    * @param
    * @param createLogGroupRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void CreateLogGroup (
        UObject *WorldContextObject,
        bool &success,
        FCreateLogGroupRequest createLogGroupRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates a log stream for the specified log group. A log stream is a sequence of log events that originate from a single source, such as an application instance or a resource that is being monitored.</p> <p>There is no limit on the number of log streams that you can create for a log group. There is a limit of 50 TPS on <code>CreateLogStream</code> operations, after which transactions are throttled.</p> <p>You must use the following guidelines when naming a log stream:</p> <ul> <li> <p>Log stream names must be unique within the log group.</p> </li> <li> <p>Log stream names can be between 1 and 512 characters long.</p> </li> <li> <p>Don't use ':' (colon) or '*' (asterisk) characters.</p> </li> </ul>
    * @param
    * @param createLogStreamRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void CreateLogStream (
        UObject *WorldContextObject,
        bool &success,
        FCreateLogStreamRequest createLogStreamRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the data protection policy from the specified log group. </p> <p>For more information about data protection policies, see <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutDataProtectionPolicy.html">PutDataProtectionPolicy</a>.</p>
    * @param
    * @param deleteDataProtectionPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteDataProtectionPolicy (
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsDeleteDataProtectionPolicyRequest deleteDataProtectionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the specified destination, and eventually disables all the subscription filters that publish to it. This operation does not delete the physical resource encapsulated by the destination.</p>
    * @param
    * @param deleteDestinationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteDestination (
        UObject *WorldContextObject,
        bool &success,
        FDeleteDestinationRequest deleteDestinationRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the specified log group and permanently deletes all the archived log events associated with the log group.</p>
    * @param
    * @param deleteLogGroupRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteLogGroup (
        UObject *WorldContextObject,
        bool &success,
        FDeleteLogGroupRequest deleteLogGroupRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the specified log stream and permanently deletes all the archived log events associated with the log stream.</p>
    * @param
    * @param deleteLogStreamRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteLogStream (
        UObject *WorldContextObject,
        bool &success,
        FDeleteLogStreamRequest deleteLogStreamRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the specified metric filter.</p>
    * @param
    * @param deleteMetricFilterRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteMetricFilter (
        UObject *WorldContextObject,
        bool &success,
        FDeleteMetricFilterRequest deleteMetricFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes a saved CloudWatch Logs Insights query definition. A query definition contains details about a saved CloudWatch Logs Insights query.</p> <p>Each <code>DeleteQueryDefinition</code> operation can delete one query definition.</p> <p>You must have the <code>logs:DeleteQueryDefinition</code> permission to be able to perform this operation.</p>
    * @param
    * @param deleteQueryDefinitionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteQueryDefinition (
        UObject *WorldContextObject,
        bool &success,
        FDeleteQueryDefinitionRequest deleteQueryDefinitionRequest,
        FDeleteQueryDefinitionResult &deleteQueryDefinitionResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes a resource policy from this account. This revokes the access of the identities in that policy to put log events to this account.</p>
    * @param
    * @param deleteResourcePolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteResourcePolicy (
        UObject *WorldContextObject,
        bool &success,
        FDeleteResourcePolicyRequest deleteResourcePolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the specified retention policy.</p> <p>Log events do not expire if they belong to log groups without a retention policy.</p>
    * @param
    * @param deleteRetentionPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteRetentionPolicy (
        UObject *WorldContextObject,
        bool &success,
        FDeleteRetentionPolicyRequest deleteRetentionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Deletes the specified subscription filter.</p>
    * @param
    * @param deleteSubscriptionFilterRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DeleteSubscriptionFilter (
        UObject *WorldContextObject,
        bool &success,
        FDeleteSubscriptionFilterRequest deleteSubscriptionFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists all your destinations. The results are ASCII-sorted by destination name.</p>
    * @param
    * @param describeDestinationsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeDestinations (
        UObject *WorldContextObject,
        bool &success,
        FDescribeDestinationsRequest describeDestinationsRequest,
        FDescribeDestinationsResult &describeDestinationsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists the specified export tasks. You can list all your export tasks or filter the results based on task ID or task status.</p>
    * @param
    * @param describeExportTasksRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeExportTasks (
        UObject *WorldContextObject,
        bool &success,
        FDescribeExportTasksRequest describeExportTasksRequest,
        FDescribeExportTasksResult &describeExportTasksResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists the specified log groups. You can list all your log groups or filter the results by prefix. The results are ASCII-sorted by log group name.</p> <p>CloudWatch Logs doesn’t support IAM policies that control access to the <code>DescribeLogGroups</code> action by using the <code>aws:ResourceTag/<i>key-name</i> </code> condition key. Other CloudWatch Logs actions do support the use of the <code>aws:ResourceTag/<i>key-name</i> </code> condition key to control access. For more information about using tags to control access, see <a href="https://docs.aws.amazon.com/IAM/latest/UserGuide/access_tags.html">Controlling access to Amazon Web Services resources using tags</a>.</p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account and view data from the linked source accounts. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>.</p>
    * @param
    * @param describeLogGroupsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeLogGroups (
        UObject *WorldContextObject,
        bool &success,
        FDescribeLogGroupsRequest describeLogGroupsRequest,
        FDescribeLogGroupsResult &describeLogGroupsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists the log streams for the specified log group. You can list all the log streams or filter the results by prefix. You can also control how the results are ordered.</p> <p>You can specify the log group to search by using either <code>logGroupIdentifier</code> or <code>logGroupName</code>. You must include one of these two parameters, but you can't include both. </p> <p>This operation has a limit of five transactions per second, after which transactions are throttled.</p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account and view data from the linked source accounts. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>.</p>
    * @param
    * @param describeLogStreamsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeLogStreams (
        UObject *WorldContextObject,
        bool &success,
        FDescribeLogStreamsRequest describeLogStreamsRequest,
        FDescribeLogStreamsResult &describeLogStreamsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists the specified metric filters. You can list all of the metric filters or filter the results by log name, prefix, metric name, or metric namespace. The results are ASCII-sorted by filter name.</p>
    * @param
    * @param describeMetricFiltersRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeMetricFilters (
        UObject *WorldContextObject,
        bool &success,
        FDescribeMetricFiltersRequest describeMetricFiltersRequest,
        FDescribeMetricFiltersResult &describeMetricFiltersResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Returns a list of CloudWatch Logs Insights queries that are scheduled, running, or have been run recently in this account. You can request all queries or limit it to queries of a specific log group or queries with a certain status.</p>
    * @param
    * @param describeQueriesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeQueries (
        UObject *WorldContextObject,
        bool &success,
        FDescribeQueriesRequest describeQueriesRequest,
        FDescribeQueriesResult &describeQueriesResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>This operation returns a paginated list of your saved CloudWatch Logs Insights query definitions.</p> <p>You can use the <code>queryDefinitionNamePrefix</code> parameter to limit the results to only the query definitions that have names that start with a certain string.</p>
    * @param
    * @param describeQueryDefinitionsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeQueryDefinitions (
        UObject *WorldContextObject,
        bool &success,
        FDescribeQueryDefinitionsRequest describeQueryDefinitionsRequest,
        FDescribeQueryDefinitionsResult &describeQueryDefinitionsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists the resource policies in this account.</p>
    * @param
    * @param describeResourcePoliciesRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeResourcePolicies (
        UObject *WorldContextObject,
        bool &success,
        FDescribeResourcePoliciesRequest describeResourcePoliciesRequest,
        FDescribeResourcePoliciesResult &describeResourcePoliciesResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists the subscription filters for the specified log group. You can list all the subscription filters or filter the results by prefix. The results are ASCII-sorted by filter name.</p>
    * @param
    * @param describeSubscriptionFiltersRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DescribeSubscriptionFilters (
        UObject *WorldContextObject,
        bool &success,
        FDescribeSubscriptionFiltersRequest describeSubscriptionFiltersRequest,
        FDescribeSubscriptionFiltersResult &describeSubscriptionFiltersResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Disassociates the associated KMS key from the specified log group.</p> <p>After the KMS key is disassociated from the log group, CloudWatch Logs stops encrypting newly ingested data for the log group. All previously ingested data remains encrypted, and CloudWatch Logs requires permissions for the KMS key whenever the encrypted data is requested.</p> <p>Note that it can take up to 5 minutes for this operation to take effect.</p>
    * @param
    * @param disassociateKmsKeyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void DisassociateKmsKey (
        UObject *WorldContextObject,
        bool &success,
        FDisassociateKmsKeyRequest disassociateKmsKeyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists log events from the specified log group. You can list all the log events or filter the results using a filter pattern, a time range, and the name of the log stream.</p> <p>You must have the <code>logs;FilterLogEvents</code> permission to perform this operation.</p> <p>You can specify the log group to search by using either <code>logGroupIdentifier</code> or <code>logGroupName</code>. You must include one of these two parameters, but you can't include both. </p> <p>By default, this operation returns as many log events as can fit in 1 MB (up to 10,000 log events) or all the events found within the specified time range. If the results include a token, that means there are more log events available. You can get additional results by specifying the token in a subsequent call. This operation can return empty results while there are more log events available through the token.</p> <p>The returned log events are sorted by event timestamp, the timestamp when the event was ingested by CloudWatch Logs, and the ID of the <code>PutLogEvents</code> request.</p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account and view data from the linked source accounts. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>.</p>
    * @param
    * @param filterLogEventsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void FilterLogEvents (
        UObject *WorldContextObject,
        bool &success,
        FFilterLogEventsRequest filterLogEventsRequest,
        FFilterLogEventsResult &filterLogEventsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Returns information about a log group data protection policy.</p>
    * @param
    * @param getDataProtectionPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void GetDataProtectionPolicy (
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsGetDataProtectionPolicyRequest getDataProtectionPolicyRequest,
        FAWSCloudWatchLogsGetDataProtectionPolicyResult &getDataProtectionPolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Lists log events from the specified log stream. You can list all of the log events or filter using a time range.</p> <p>By default, this operation returns as many log events as can fit in a response size of 1MB (up to 10,000 log events). You can get additional log events by specifying one of the tokens in a subsequent call. This operation can return empty results while there are more log events available through the token.</p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account and view data from the linked source accounts. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>.</p> <p>You can specify the log group to search by using either <code>logGroupIdentifier</code> or <code>logGroupName</code>. You must include one of these two parameters, but you can't include both. </p>
    * @param
    * @param getLogEventsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void GetLogEvents (
        UObject *WorldContextObject,
        bool &success,
        FGetLogEventsRequest getLogEventsRequest,
        FGetLogEventsResult &getLogEventsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Returns a list of the fields that are included in log events in the specified log group. Includes the percentage of log events that contain each field. The search is limited to a time period that you specify.</p> <p>You can specify the log group to search by using either <code>logGroupIdentifier</code> or <code>logGroupName</code>. You must specify one of these parameters, but you can't specify both. </p> <p>In the results, fields that start with <code>@</code> are fields generated by CloudWatch Logs. For example, <code>@timestamp</code> is the timestamp of each log event. For more information about the fields that are generated by CloudWatch logs, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/CWL_AnalyzeLogData-discoverable-fields.html">Supported Logs and Discovered Fields</a>.</p> <p>The response results are sorted by the frequency percentage, starting with the highest percentage.</p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account and view data from the linked source accounts. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>.</p>
    * @param
    * @param getLogGroupFieldsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void GetLogGroupFields (
        UObject *WorldContextObject,
        bool &success,
        FGetLogGroupFieldsRequest getLogGroupFieldsRequest,
        FGetLogGroupFieldsResult &getLogGroupFieldsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Retrieves all of the fields and values of a single log event. All fields are retrieved, even if the original query that produced the <code>logRecordPointer</code> retrieved only a subset of fields. Fields are returned as field name/field value pairs.</p> <p>The full unparsed log event is returned within <code>@message</code>.</p>
    * @param
    * @param getLogRecordRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void GetLogRecord (
        UObject *WorldContextObject,
        bool &success,
        FGetLogRecordRequest getLogRecordRequest,
        FGetLogRecordResult &getLogRecordResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Returns the results from the specified query.</p> <p>Only the fields requested in the query are returned, along with a <code>@ptr</code> field, which is the identifier for the log record. You can use the value of <code>@ptr</code> in a <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_GetLogRecord.html">GetLogRecord</a> operation to get the full log record.</p> <p> <code>GetQueryResults</code> does not start running a query. To run a query, use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_StartQuery.html">StartQuery</a>.</p> <p>If the value of the <code>Status</code> field in the output is <code>Running</code>, this operation returns only partial results. If you see a value of <code>Scheduled</code> or <code>Running</code> for the status, you can retry the operation later to see the final results. </p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account to start queries in linked source accounts. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>.</p>
    * @param
    * @param getQueryResultsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void GetQueryResults (
        UObject *WorldContextObject,
        bool &success,
        FGetQueryResultsRequest getQueryResultsRequest,
        FGetQueryResultsResult &getQueryResultsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Displays the tags associated with a CloudWatch Logs resource. Currently, log groups and destinations support tagging.</p>
    * @param
    * @param listTagsForResourceRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void ListTagsForResource (
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsListTagsForResourceRequest listTagsForResourceRequest,
        FAWSCloudWatchLogsListTagsForResourceResult &listTagsForResourceResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates a data protection policy for the specified log group. A data protection policy can help safeguard sensitive data that's ingested by the log group by auditing and masking the sensitive log data.</p> <important> <p>Sensitive data is detected and masked when it is ingested into the log group. When you set a data protection policy, log events ingested into the log group before that time are not masked.</p> </important> <p>By default, when a user views a log event that includes masked data, the sensitive data is replaced by asterisks. A user who has the <code>logs:Unmask</code> permission can use a <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_GetLogEvents.html">GetLogEvents</a> or <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_FilterLogEvents.html">FilterLogEvents</a> operation with the <code>unmask</code> parameter set to <code>true</code> to view the unmasked log events. Users with the <code>logs:Unmask</code> can also view unmasked data in the CloudWatch Logs console by running a CloudWatch Logs Insights query with the <code>unmask</code> query command.</p> <p>For more information, including a list of types of data that can be audited and masked, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/mask-sensitive-log-data.html">Protect sensitive log data with masking</a>.</p>
    * @param
    * @param putDataProtectionPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutDataProtectionPolicy (
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsPutDataProtectionPolicyRequest putDataProtectionPolicyRequest,
        FAWSCloudWatchLogsPutDataProtectionPolicyResult &putDataProtectionPolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates or updates a destination. This operation is used only to create destinations for cross-account subscriptions.</p> <p>A destination encapsulates a physical resource (such as an Amazon Kinesis stream). With a destination, you can subscribe to a real-time stream of log events for a different account, ingested using <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutLogEvents.html">PutLogEvents</a>.</p> <p>Through an access policy, a destination controls what is written to it. By default, <code>PutDestination</code> does not set any access policy with the destination, which means a cross-account user cannot call <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutSubscriptionFilter.html">PutSubscriptionFilter</a> against this destination. To enable this, the destination owner must call <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutDestinationPolicy.html">PutDestinationPolicy</a> after <code>PutDestination</code>.</p> <p>To perform a <code>PutDestination</code> operation, you must also have the <code>iam:PassRole</code> permission.</p>
    * @param
    * @param putDestinationRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutDestination (
        UObject *WorldContextObject,
        bool &success,
        FPutDestinationRequest putDestinationRequest,
        FPutDestinationResult &putDestinationResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates or updates an access policy associated with an existing destination. An access policy is an <a href="https://docs.aws.amazon.com/IAM/latest/UserGuide/policies_overview.html">IAM policy document</a> that is used to authorize claims to register a subscription filter against a given destination.</p>
    * @param
    * @param putDestinationPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutDestinationPolicy (
        UObject *WorldContextObject,
        bool &success,
        FPutDestinationPolicyRequest putDestinationPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    *  An Async wrapper for PutLogEvents that queues the request into a thread executor and triggers associated callback when operation has finished.
    * @param
    * @param putLogEventsRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutLogEvents (
        UObject *WorldContextObject,
        bool &success,
        FPutLogEventsRequest putLogEventsRequest,
        FPutLogEventsResult &putLogEventsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates or updates a metric filter and associates it with the specified log group. With metric filters, you can configure rules to extract metric data from log events ingested through <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutLogEvents.html">PutLogEvents</a>.</p> <p>The maximum number of metric filters that can be associated with a log group is 100.</p> <p>When you create a metric filter, you can also optionally assign a unit and dimensions to the metric that is created.</p> <important> <p>Metrics extracted from log events are charged as custom metrics. To prevent unexpected high charges, do not specify high-cardinality fields such as <code>IPAddress</code> or <code>requestID</code> as dimensions. Each different value found for a dimension is treated as a separate metric and accrues charges as a separate custom metric. </p> <p>CloudWatch Logs disables a metric filter if it generates 1,000 different name/value pairs for your specified dimensions within a certain amount of time. This helps to prevent accidental high charges.</p> <p>You can also set up a billing alarm to alert you if your charges are higher than expected. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/monitor_estimated_charges_with_cloudwatch.html"> Creating a Billing Alarm to Monitor Your Estimated Amazon Web Services Charges</a>. </p> </important>
    * @param
    * @param putMetricFilterRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutMetricFilter (
        UObject *WorldContextObject,
        bool &success,
        FPutMetricFilterRequest putMetricFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates or updates a query definition for CloudWatch Logs Insights. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/AnalyzingLogData.html">Analyzing Log Data with CloudWatch Logs Insights</a>.</p> <p>To update a query definition, specify its <code>queryDefinitionId</code> in your request. The values of <code>name</code>, <code>queryString</code>, and <code>logGroupNames</code> are changed to the values that you specify in your update operation. No current values are retained from the current query definition. For example, imagine updating a current query definition that includes log groups. If you don't specify the <code>logGroupNames</code> parameter in your update operation, the query definition changes to contain no log groups.</p> <p>You must have the <code>logs:PutQueryDefinition</code> permission to be able to perform this operation.</p>
    * @param
    * @param putQueryDefinitionRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutQueryDefinition (
        UObject *WorldContextObject,
        bool &success,
        FPutQueryDefinitionRequest putQueryDefinitionRequest,
        FPutQueryDefinitionResult &putQueryDefinitionResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates or updates a resource policy allowing other Amazon Web Services services to put log events to this account, such as Amazon Route 53. An account can have up to 10 resource policies per Amazon Web Services Region.</p>
    * @param
    * @param putResourcePolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutResourcePolicy (
        UObject *WorldContextObject,
        bool &success,
        FPutResourcePolicyRequest putResourcePolicyRequest,
        FPutResourcePolicyResult &putResourcePolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Sets the retention of the specified log group. With a retention policy, you can configure the number of days for which to retain log events in the specified log group.</p> <note> <p>CloudWatch Logs doesn’t immediately delete log events when they reach their retention setting. It typically takes up to 72 hours after that before log events are deleted, but in rare situations might take longer.</p> <p>To illustrate, imagine that you change a log group to have a longer retention setting when it contains log events that are past the expiration date, but haven’t been deleted. Those log events will take up to 72 hours to be deleted after the new retention date is reached. To make sure that log data is deleted permanently, keep a log group at its lower retention setting until 72 hours after the previous retention period ends. Alternatively, wait to change the retention setting until you confirm that the earlier log events are deleted. </p> </note>
    * @param
    * @param putRetentionPolicyRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutRetentionPolicy (
        UObject *WorldContextObject,
        bool &success,
        FPutRetentionPolicyRequest putRetentionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Creates or updates a subscription filter and associates it with the specified log group. With subscription filters, you can subscribe to a real-time stream of log events ingested through <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutLogEvents.html">PutLogEvents</a> and have them delivered to a specific destination. When log events are sent to the receiving service, they are Base64 encoded and compressed with the GZIP format.</p> <p>The following destinations are supported for subscription filters:</p> <ul> <li> <p>An Amazon Kinesis data stream belonging to the same account as the subscription filter, for same-account delivery.</p> </li> <li> <p>A logical destination that belongs to a different account, for cross-account delivery.</p> </li> <li> <p>An Amazon Kinesis Data Firehose delivery stream that belongs to the same account as the subscription filter, for same-account delivery.</p> </li> <li> <p>An Lambda function that belongs to the same account as the subscription filter, for same-account delivery.</p> </li> </ul> <p>Each log group can have up to two subscription filters associated with it. If you are updating an existing filter, you must specify the correct name in <code>filterName</code>. </p> <p>To perform a <code>PutSubscriptionFilter</code> operation, you must also have the <code>iam:PassRole</code> permission.</p>
    * @param
    * @param putSubscriptionFilterRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void PutSubscriptionFilter (
        UObject *WorldContextObject,
        bool &success,
        FPutSubscriptionFilterRequest putSubscriptionFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Schedules a query of a log group using CloudWatch Logs Insights. You specify the log group and time range to query and the query string to use.</p> <p>For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/CWL_QuerySyntax.html">CloudWatch Logs Insights Query Syntax</a>.</p> <p>Queries time out after 15 minutes of runtime. If your queries are timing out, reduce the time range being searched or partition your query into a number of queries.</p> <p>If you are using CloudWatch cross-account observability, you can use this operation in a monitoring account to start a query in a linked source account. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/CloudWatch-Unified-Cross-Account.html">CloudWatch cross-account observability</a>. For a cross-account <code>StartQuery</code> operation, the query definition must be defined in the monitoring account.</p> <p>You can have up to 20 concurrent CloudWatch Logs insights queries, including queries that have been added to dashboards. </p>
    * @param
    * @param startQueryRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void StartQuery (
        UObject *WorldContextObject,
        bool &success,
        FStartQueryRequest startQueryRequest,
        FStartQueryResult &startQueryResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Stops a CloudWatch Logs Insights query that is in progress. If the query has already ended, the operation returns an error indicating that the specified query is not running.</p>
    * @param
    * @param stopQueryRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void StopQuery (
        UObject *WorldContextObject,
        bool &success,
        FStopQueryRequest stopQueryRequest,
        FStopQueryResult &stopQueryResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Assigns one or more tags (key-value pairs) to the specified CloudWatch Logs resource. Currently, the only CloudWatch Logs resources that can be tagged are log groups and destinations. </p> <p>Tags can help you organize and categorize your resources. You can also use them to scope user permissions by granting a user permission to access or change only resources with certain tag values.</p> <p>Tags don't have any semantic meaning to Amazon Web Services and are interpreted strictly as strings of characters.</p> <p>You can use the <code>TagResource</code> action with a resource that already has tags. If you specify a new tag key for the alarm, this tag is appended to the list of tags associated with the alarm. If you specify a tag key that is already associated with the alarm, the new tag value that you specify replaces the previous value for that tag.</p> <p>You can associate as many as 50 tags with a CloudWatch Logs resource.</p>
    * @param
    * @param tagResourceRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void TagResource (
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsTagResourceRequest tagResourceRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Tests the filter pattern of a metric filter against a sample of log event messages. You can use this operation to validate the correctness of a metric filter pattern.</p>
    * @param
    * @param testMetricFilterRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void TestMetricFilter (
        UObject *WorldContextObject,
        bool &success,
        FTestMetricFilterRequest testMetricFilterRequest,
        FTestMetricFilterResult &testMetricFilterResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
    /**
    * <p>Removes one or more tags from the specified resource.</p>
    * @param
    * @param untagResourceRequest
    * @param LatentInfo         The latent action
    **/
    UFUNCTION(BlueprintCallable,
    meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
    Category = "CloudWatchLogs Client")
    void UntagResource (
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsUntagResourceRequest untagResourceRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
    );
};
